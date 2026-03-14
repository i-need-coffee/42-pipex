/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:41:31 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 14:07:38 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
