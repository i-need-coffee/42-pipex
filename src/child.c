/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:41:31 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/12 18:26:56 by sjolliet         ###   ########.fr       */
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
		cleanup_and_exit(p_data, strerror(errno));
	if (dup2(p_data->fds[1], STDOUT_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno));
	close_fds(p_data);
	char *args[] = {"/bin/grep", "a1", NULL};
	if (execve("/bin/grep", args, envp) == -1)
		cleanup_and_exit(p_data, strerror(errno));
	ft_printf("cmd: %s\n", cmd);
}

void	second_child(t_pipe_data *p_data, char *cmd, char **envp)
{
	if (dup2(p_data->fds[0], STDIN_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno));
	if (dup2(p_data->fd_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno));
	close_fds(p_data);
	char *args[] = {"/usr/bin/wc", "-w", NULL};
	if (execve("/usr/bin/wc", args, envp) == -1)
		cleanup_and_exit(p_data, strerror(errno));
	ft_printf("cmd: %s\n", cmd);
}
