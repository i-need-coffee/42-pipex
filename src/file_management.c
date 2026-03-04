/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:01:12 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/04 19:49:47 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_read_fd(char *filepath)
{
	char	*msg;
	char	*error_msg;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		if (access(filepath, F_OK) == -1)
			msg = "no such file or directory: ";
		else if (access("file.txt", R_OK) == -1)
			msg = "permission denied: ";
		else
			msg = "file could not be opened: ";
		error_msg = ft_strjoin(msg, filepath);
		if (!error_msg)
			show_error_and_exit("memory allocation failed");
		show_error(error_msg);
		free(error_msg);
	}
	return (fd);
}
