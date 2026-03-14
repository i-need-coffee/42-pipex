/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:10 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 16:06:54 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	safe_close(int *fd);

void	throw_error(char *err_msg, char *err_loc)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_loc, 2);
	ft_putstr_fd("\n", 2);
}

void	cleanup_and_exit(t_pipe_data *p_data, char *err_msg, char *err_loc)
{
	close_fds(p_data);
	throw_error(err_msg, err_loc);
	exit(EXIT_FAILURE);
}

void	close_fds(t_pipe_data *p_data)
{
	safe_close(&p_data->fd_in);
	safe_close(&p_data->fd_out);
	safe_close(&p_data->fds[0]);
	safe_close(&p_data->fds[1]);
}

void	free_exec_data(t_exec_data *e_data)
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

static void	safe_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}
