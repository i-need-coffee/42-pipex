/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:26:47 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/12 18:29:20 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **envp);
static void	exec_error(t_exec_data *e_data, t_pipe_data *p_data, char *error_msg);
static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data);
static void	set_valid_path(t_exec_data *e_data, t_pipe_data *p_data);

void	execute_cmd(t_pipe_data *p_data, char **envp, char *arg)
{
	t_exec_data e_data;

	ft_bzero(&e_data, sizeof(e_data));
	e_data.paths = get_paths(envp);
	if (!e_data.paths)
		cleanup_and_exit(p_data, "Problem with retrieving paths");
	e_data.cmd = ft_split(arg, ' ');
	if (!e_data.cmd)
		exec_error(&e_data, p_data, "Memory allocation failed");
	set_valid_path(&e_data, p_data);
	if (execve(e_data.full_path, e_data.cmd, envp) == -1)
		exec_error(&e_data, p_data, strerror(errno));
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

static void	exec_error(t_exec_data *e_data, t_pipe_data *p_data, char *error_msg)
{
	if (e_data->paths)
		free_char_tab(e_data->paths);
	if (e_data->cmd)
		free_char_tab(e_data->cmd);
	if (e_data->full_path)
		free(e_data->full_path);
	if (e_data->j_cmd)
		free(e_data->j_cmd);
	if (e_data->err_msg)
		free(e_data->err_msg);
	cleanup_and_exit(p_data, error_msg);
}

static void	check_access_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	if (!e_data->full_path)
	{
		e_data->err_msg = ft_strjoin("Command not found: ", e_data->cmd[0]);
		if (!e_data->err_msg)
			exec_error(e_data, p_data, "Memory allocation failed");
		exec_error(e_data, p_data, e_data->err_msg);
	}
	if (access(e_data->full_path, X_OK) == -1)
	{
		e_data->err_msg = ft_strjoin("Command not executable: ", e_data->cmd[0]);
		if (!e_data->err_msg)
			exec_error(e_data, p_data, "Memory allocation failed");
		exec_error(e_data, p_data, e_data->err_msg);
	}
}

static void	set_valid_path(t_exec_data *e_data, t_pipe_data *p_data)
{
	int		i;

	e_data->j_cmd = ft_strjoin("/", e_data->cmd[0]);
	if (!e_data->j_cmd)
		exec_error(e_data, p_data, "Memory allocation failed");
	i = 0;
	while (e_data->paths[i])
	{
		e_data->full_path = ft_strjoin(e_data->paths[i], e_data->j_cmd);
		if (!e_data->full_path)
			exec_error(e_data, p_data, "Memory allocation failed");
		if (access(e_data->full_path, F_OK) == 0)
			break ;
		free(e_data->full_path);
		i++;
	}
	check_access_path(e_data, p_data);
}
