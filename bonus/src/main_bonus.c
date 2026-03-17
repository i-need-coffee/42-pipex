/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 16:34:37 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	p_data;

	ft_memset(&p_data, -1, sizeof(p_data));
	if (argc != 5)
		cleanup_and_exit(&p_data, "Program needs 4 args", "pipex");
	open_files(&p_data, argv);
	if (pipe(p_data.fds) == -1)
		cleanup_and_exit(&p_data, strerror(errno), "pipe");
	p_data.pid1 = fork();
	if (p_data.pid1 == -1)
		cleanup_and_exit(&p_data, strerror(errno), "fork 1");
	if (p_data.pid1 == 0)
		first_child(&p_data, argv[2], envp);
	p_data.pid2 = fork();
	if (p_data.pid2 == -1)
		cleanup_and_exit(&p_data, strerror(errno), "fork 2");
	if (p_data.pid2 == 0)
		second_child(&p_data, argv[3], envp);
	close_fds(&p_data);
	if (waitpid(p_data.pid1, NULL, 0) == -1)
		cleanup_and_exit(&p_data, strerror(errno), "waitpid 1");
	if (waitpid(p_data.pid2, NULL, 0) == -1)
		cleanup_and_exit(&p_data, strerror(errno), "waitpid 1");
	return (0);
}
