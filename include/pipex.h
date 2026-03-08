/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:01:32 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/08 23:28:30 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipe_data
{
	int		fds[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid1;
	pid_t	pid2;
}			t_pipe_data;

void	cleanup_and_exit(t_pipe_data *p_data, char *error_msg);
void	open_files(t_pipe_data *pipes, char **argv);
void	close_fds(t_pipe_data *p_data);
void	first_child(t_pipe_data *p_data, char *cmd, char **envp);
void	second_child(t_pipe_data *p_data, char *cmd, char **envp);

#endif