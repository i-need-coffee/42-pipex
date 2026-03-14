/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:26:47 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 14:28:34 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **envp);
static void	free_exec_data(t_exec_data *e_data);
static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data);
static void	set_valid_path(t_exec_data *e_data, t_pipe_data *p_data);

void	execute_cmd(t_pipe_data *p_data, char **envp, char *arg)
{
	t_exec_data e_data;
	int			err_num;

	ft_bzero(&e_data, sizeof(e_data));
	e_data.paths = get_paths(envp);
	if (!e_data.paths)
		cleanup_and_exit(p_data, "Problem with paths", "envp");
	e_data.cmd = ft_split(arg, ' ');
	if (!e_data.cmd)
	{
		free_exec_data(&e_data);
		cleanup_and_exit(p_data, "Memory allocation failed", "ft_split");
	}
	set_valid_path(&e_data, p_data);
	if (execve(e_data.full_path, e_data.cmd, envp) == -1)
	{
		err_num = errno;
		free_exec_data(&e_data);
		cleanup_and_exit(p_data, strerror(err_num), "execve");
	}
}

static char	**get_paths(char **envp)
{
	char	**paths;
	char	*path_str;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	free(path_str);
	return (paths);
}

static void	free_exec_data(t_exec_data *e_data)
{
	if (e_data->paths)
		free_char_tab(e_data->paths);
	if (e_data->cmd)
		free_char_tab(e_data->cmd);
	if (e_data->full_path)
		free(e_data->full_path);
	if (e_data->j_cmd)
		free(e_data->j_cmd);
}

static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	if (access(e_data->full_path, F_OK) == -1)
	{
		perror(e_data->cmd[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
	if (access(e_data->full_path, X_OK) == -1)
	{
		perror(e_data->cmd[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
}

static void	set_valid_path(t_exec_data *e_data, t_pipe_data *p_data)
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
