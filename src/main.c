/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/06 11:26:15 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	pipefds[2];

	if (argc != 5)
		show_error_and_exit("Program needs 4 arguments");
	pipefds[0] = open(argv[1], O_RDONLY);
	if (pipefds[0] == -1)
		perror(argv[1]);
	if (pipefds[0] != -1)
		close(pipefds[0]);
	return (0);
}
