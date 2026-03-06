/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/06 18:05:47 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipe_data	p_data;

	if (argc != 5)
		show_error_and_exit("Program needs 4 arguments");
	if (pipe(p_data.fds) == -1)
		show_error_and_exit(strerror(errno));
	open_files(&p_data, argv);
	p_data.pid1 = fork();
	if (p_data.pid1 == -1)
	{
		close_fds(&p_data);
		show_error_and_exit(strerror(errno));
	}
	close_fds(&p_data);
	return (0);
}
