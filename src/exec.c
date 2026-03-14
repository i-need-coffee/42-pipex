/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:26:47 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 19:04:31 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_args(t_pipe_data *p_data, t_exec_data *e_data, char *arg);
static void	set_path(t_pipe_data *p_data, t_exec_data *e_data, char **envp);
static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data);
static void	find_valid_path(t_exec_data *e_data, t_pipe_data *p_data);

void	execute_cmd(t_pipe_data *p_data, char **envp, char *arg)
{
	t_exec_data	e_data;
	int			err_num;
	int			i;
	char		*temp;

	ft_bzero(&e_data, sizeof(e_data));
	set_args(p_data, &e_data, arg);
	i = 0;
	while(e_data.cmd[i])
	{
		temp = ft_strtrim(e_data.cmd[i], " ");
		if (!temp)
			cleanup_and_exit(p_data, "Memory allocation failed", "ft_strtrim");
		free(e_data.cmd[i]);
		e_data.cmd[i] = temp;
		i++;
	}
	set_path(p_data, &e_data, envp);
	if (execve(e_data.full_path, e_data.cmd, envp) == -1)
	{
		err_num = errno;
		free_exec_data(&e_data);
		cleanup_and_exit(p_data, strerror(err_num), "execve");
	}
}

static void	set_args(t_pipe_data *p_data, t_exec_data *e_data, char *arg)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		e_data->cmd = ft_split(arg, '\'');
	else
		e_data->cmd = ft_split(arg, ' ');
	if (!e_data->cmd)
		cleanup_and_exit(p_data, "Memory allocation failed", "ft_split");
}

static void	set_path(t_pipe_data *p_data, t_exec_data *e_data, char **envp)
{
	if (e_data->cmd[0] && e_data->cmd[0][0] == '/')
	{
		e_data->full_path = e_data->cmd[0];
		check_access_path(e_data, p_data);
	}
	else
	{
		e_data->paths = get_paths(envp);
		if (!e_data->paths)
		{
			free_exec_data(e_data);
			cleanup_and_exit(p_data, "Problem with paths", "envp");
		}
		find_valid_path(e_data, p_data);
	}
}

static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	if (access(e_data->full_path, F_OK) == -1)
	{
		throw_error("Command not found", e_data->cmd[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
	if (access(e_data->full_path, X_OK) == -1)
	{
		throw_error("Command not exectuable", e_data->cmd[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
}

static void	find_valid_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	int		i;

	e_data->j_cmd = ft_strjoin("/", e_data->cmd[0]);
	if (!e_data->j_cmd)
	{
		free_exec_data(e_data);
		cleanup_and_exit(p_data, "Memory allocation failed", "ft_strjoin");
	}
	i = 0;
	while (e_data->paths[i])
	{
		free_and_null(&e_data->full_path);
		e_data->full_path = ft_strjoin(e_data->paths[i], e_data->j_cmd);
		if (!e_data->full_path)
		{
			free_exec_data(e_data);
			cleanup_and_exit(p_data, "Memory allocation failed", "ft_strjoin");
		}
		if (access(e_data->full_path, F_OK) == 0)
			break ;
		i++;
	}
	check_access_path(e_data, p_data);
}
