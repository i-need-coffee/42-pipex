/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:41:31 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 21:43:24 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_files(t_pipe_data *p_data, char **argv, int argc)
{
	p_data->fd_in = open(argv[1], O_RDONLY);
	if (p_data->fd_in == -1)
		throw_error(strerror(errno), argv[1]);
	p_data->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_data->fd_out == -1)
		cleanup_and_exit(p_data, strerror(errno), argv[argc - 1]);
}

void	init_pipe_data(t_pipe_data *p_data)
{
	p_data->num_cmds = 0;
	p_data->pipes = NULL;
	p_data->p_count = 0;
	p_data->fd_in = -1;
	p_data->fd_out = -1;
}

void	free_pipe_data(t_pipe_data *p_data)
{
	int	i;

	if (!p_data->pipes)
		return ;
	i = 0;
	while (i < p_data->p_count)
	{
		if (p_data->pipes[i])
			free(p_data->pipes[i]);
		i++;
	}
	free(p_data->pipes);
	p_data->pipes = NULL;
}

void	create_pipes(t_pipe_data *p_data)
{
	int	i;

	p_data->p_count = p_data->num_cmds - 1;
	p_data->pipes = malloc(p_data->p_count * sizeof(int *));
	if (!p_data->pipes)
		cleanup_and_exit(p_data, "pipes creation failed", "malloc");
	i = 0;
	while (i < p_data->p_count)
	{
		p_data->pipes[i] = malloc(2 * sizeof(int));
		if (!p_data->pipes[i])
			cleanup_and_exit(p_data, "pipes creation failed", "malloc");
		i++;
	}
	i = 0;
	while (i < p_data->p_count)
	{
		if (pipe(p_data->pipes[i]) == -1)
			cleanup_and_exit(p_data, strerror(errno), "pipe");
		i++;
	}
}

void	create_children(t_pipe_data *p_data, char **argv, char **envp)
{
	int	i;

	p_data->pids = malloc(p_data->num_cmds * sizeof(pid_t));
	if (!p_data->pids)
		cleanup_and_exit(&p_data, "pids array creation failed", "malloc");
	i = 0;
	while (i < p_data->num_cmds)
	{
		p_data->pids[i] = fork();
		if (p_data->pids[i] == -1)
			cleanup_and_exit(&p_data, strerror(errno), "fork");
		if (p_data->pids[i] == 0)
		{
			if (i == 0)
				child_process(p_data->fd_in, p_data->pipes[i][1],
					p_data, argv[i + 2], envp);
			else if (i == (p_data->num_cmds - 1))
				child_process(p_data->pipes[i][0], p_data->fd_out,
					p_data, argv[i + 2], envp);
			else
				child_process(p_data->pipes[i][0], p_data->pipes[i + 1][1],
					p_data, argv[i + 2], envp);
		}
		i++;
	}
}
