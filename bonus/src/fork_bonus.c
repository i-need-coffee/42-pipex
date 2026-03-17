/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:49:18 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 22:27:17 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(t_pipe_data *p_data, char *cmd, int i, char **envp);
static void	dup_child(t_pipe_data *p_data, int fd_in, int fd_out);

void	create_children(t_pipe_data *p_data, char **argv, char **envp)
{
	int	i;

	p_data->pids = malloc(p_data->num_cmds * sizeof(pid_t));
	if (!p_data->pids)
		cleanup_and_exit(p_data, "pids array creation failed", "malloc");
	i = 0;
	while (i < p_data->num_cmds)
	{
		p_data->pids[i] = fork();
		if (p_data->pids[i] == -1)
			cleanup_and_exit(p_data, strerror(errno), "fork");
		if (p_data->pids[i] == 0)
			child_process(p_data, argv[i + 2], i, envp);
		i++;
	}
}

static void	child_process(t_pipe_data *p_data, char *cmd, int i, char **envp)
{
	if (i == 0)
	{
		if (p_data->fd_in == -1)
		{
			close_fds(p_data);
			free_pipe_data(p_data);
			exit(EXIT_FAILURE);
		}
		dup_child(p_data, p_data->fd_in, p_data->pipes[i][1]);
	}
	else if (i == (p_data->num_cmds - 1))
		dup_child(p_data, p_data->pipes[i][0], p_data->fd_out);
	else
		dup_child(p_data, p_data->pipes[i][0], p_data->pipes[i + 1][1]);
	execute_cmd(p_data, envp, cmd);
}

static void	dup_child(t_pipe_data *p_data, int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(p_data, strerror(errno), "dup2");
	close_fds(p_data);
	free_pipe_data(p_data);
}
