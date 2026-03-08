/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/08 21:54:41 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	p_data;

	ft_bzero(&p_data, sizeof(p_data));
	if (argc != 5)
		cleanup_and_exit(&p_data, "Program needs 4 arguments");
	open_files(&p_data, argv);
	if (pipe(p_data.fds) == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	if (p_data.fd_in != -1)
		run_infile_cmd(&p_data, argv[2], envp);
	if (p_data.fd_out != -1)
		run_outfile_cmd(&p_data, argv[3], envp);
	close_fds(&p_data);
	waitpid(p_data.pid1, NULL, 0);
	waitpid(p_data.pid2, NULL, 0);
	return (0);
}
