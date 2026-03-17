/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 22:24:01 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	p_data;

	init_pipe_data(&p_data);
	if (argc < 5)
		cleanup_and_exit(&p_data, "Program needs at least 4 args", "pipex");
	open_files(&p_data, argv, argc);
	p_data.num_cmds = argc - 3;
	create_pipes(&p_data);
	create_children(&p_data, argv, envp);
	close_fds(&p_data);
	free_pipe_data(&p_data);
	free(p_data.pids);
	return (0);
}
