/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:10 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 22:27:22 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	throw_error(char *err_msg, char *err_loc)
{
	write(2, "\033[31mERROR\033[0m ", 16);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, err_loc, ft_strlen(err_loc));
	write(2, "\n", 1);
}

void	cleanup_and_exit(t_pipe_data *p_data, char *err_msg, char *err_loc)
{
	close_fds(p_data);
	free_pipe_data(p_data);
	throw_error(err_msg, err_loc);
	exit(EXIT_FAILURE);
}

void	close_fds(t_pipe_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->p_count)
	{
		safe_close(&p_data->pipes[i][0]);
		safe_close(&p_data->pipes[i][1]);
		i++;
	}
	safe_close(&p_data->fd_in);
	safe_close(&p_data->fd_out);
}

void	free_exec_data(t_exec_data *e_data)
{
	if (e_data->paths)
		free_char_tab(e_data->paths);
	if (e_data->args)
		free_char_tab(e_data->args);
	if (e_data->full_path)
		free(e_data->full_path);
	if (e_data->j_cmd)
		free(e_data->j_cmd);
}

void	free_args(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
