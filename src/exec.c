/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:26:47 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/15 15:40:47 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **envp);
static void	set_path(t_pipe_data *p_data, t_exec_data *e_data, char **envp);
static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data);
static void	find_valid_path(t_exec_data *e_data, t_pipe_data *p_data);

void	execute_cmd(t_pipe_data *p_data, char **envp, char *cmd)
{
	t_exec_data	e_data;
	int			err_num;

	ft_bzero(&e_data, sizeof(e_data));
	e_data.args = create_args(cmd);
	if (!e_data.args)
		cleanup_and_exit(p_data, "Problem with creating args", cmd);
	set_path(p_data, &e_data, envp);
	if (execve(e_data.full_path, e_data.args, envp) == -1)
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
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp || !envp[i])
		return (NULL);
	path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	free(path_str);
	return (paths);
}

static void	set_path(t_pipe_data *p_data, t_exec_data *e_data, char **envp)
{
	if (e_data->args[0] && e_data->args[0][0] == '/')
	{
		e_data->full_path = e_data->args[0];
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
		throw_error("Command not found", e_data->args[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
	if (access(e_data->full_path, X_OK) == -1)
	{
		throw_error("Command not exectuable", e_data->args[0]);
		free_exec_data(e_data);
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
}

static void	find_valid_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	int		i;

	e_data->j_cmd = ft_strjoin("/", e_data->args[0]);
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
