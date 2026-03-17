/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/18 00:37:32 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	p_data;

	init_pipe_data(&p_data);
	if (argc < 5)
		cleanup_and_exit(&p_data, "Program needs at least 4 args", "pipex");
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
	{
		p_data.here_doc = 1;
		p_data.num_cmds = argc - 4;
	}
	else
		p_data.num_cmds = argc - 3;
	if (p_data.here_doc)
		handle_here_doc(&p_data, argv[2]);
	open_files(&p_data, argv, argc);
	create_pipes(&p_data);
	create_children(&p_data, argv, envp);
	close_fds(&p_data);
	wait_children(&p_data);
	free_pipe_data(&p_data);
	return (0);
}
