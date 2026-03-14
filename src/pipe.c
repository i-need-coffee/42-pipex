/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:41:31 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 15:08:58 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipe_data *p_data, char **argv)
{
	p_data->fd_in = open(argv[1], O_RDONLY);
	if (p_data->fd_in == -1)
		throw_error(strerror(errno), argv[1]);
	p_data->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_data->fd_out == -1)
		cleanup_and_exit(p_data, strerror(errno), argv[4]);
}

void	first_child(t_pipe_data *p_data, char *cmd, char **envp)
{
	if (p_data->fd_in == -1)
	{
		close_fds(p_data);
		exit(EXIT_FAILURE);
	}
	if (dup2(p_data->fd_in, STDIN_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	if (dup2(p_data->fds[1], STDOUT_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	close_fds(p_data);
	execute_cmd(p_data, envp, cmd);
}

void	second_child(t_pipe_data *p_data, char *cmd, char **envp)
{
	if (dup2(p_data->fds[0], STDIN_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	if (dup2(p_data->fd_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	close_fds(p_data);
	execute_cmd(p_data, envp, cmd);
}
