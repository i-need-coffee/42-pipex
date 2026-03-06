/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/06 14:11:47 by sjolliet         ###   ########.fr       */
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
	pipefds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipefds[1] == -1)
		perror(argv[4]);
	if (pipefds[0] != -1)
		close(pipefds[0]);
	if (pipefds[1] != -1)
		close(pipefds[1]);
	return (0);
}
