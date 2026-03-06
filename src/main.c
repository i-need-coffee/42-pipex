/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/06 18:59:01 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipe_data	p_data;

	ft_bzero(&p_data, sizeof(p_data));
	if (argc != 5)
		cleanup_and_exit(&p_data, "Program needs 4 arguments");
	if (pipe(p_data.fds) == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	open_files(&p_data, argv);
	p_data.pid1 = fork();
	if (p_data.pid1 == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	if (p_data.pid1 == 0)
	{
		if (dup2(p_data.fd_in, 0) == -1)
			cleanup_and_exit(&p_data, strerror(errno));
		if (dup2(p_data.fds[1], 1) == -1)
			cleanup_and_exit(&p_data, strerror(errno));
	}
	close_fds(&p_data);
	return (0);
}
