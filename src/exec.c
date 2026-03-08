/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:41:31 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/08 21:49:11 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_infile_cmd(t_pipe_data *p_data, char *cmd, char **envp)
{
	p_data->pid1 = fork();
	if (p_data->pid1 == -1)
		cleanup_and_exit(p_data, strerror(errno));
	if (p_data->pid1 > 0)
		return ;
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

void	run_outfile_cmd(t_pipe_data *p_data, char *cmd, char **envp)
{
	p_data->pid2 = fork();
	if (p_data->pid2 == -1)
		cleanup_and_exit(p_data, strerror(errno));
	if (p_data->pid2 > 0)
		return ;
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
