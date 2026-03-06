/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:10 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/06 17:53:58 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	safe_close(int fd);

void	show_error_and_exit(char *error_msg)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	open_files(t_pipe_data *p_data, char **argv)
{
	p_data->fd_in = open(argv[1], O_RDONLY);
	if (p_data->fd_in == -1)
		perror(argv[1]);
	p_data->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_data->fd_out == -1)
		perror(argv[4]);
}

void	close_fds(t_pipe_data *p_data)
{
	safe_close(p_data->fd_in);
	safe_close(p_data->fd_out);
	safe_close(p_data->fds[0]);
	safe_close(p_data->fds[1]);
}

static void	safe_close(int fd)
{
	if (fd && fd != -1)
		close(fd);
}
