/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:01:32 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/14 16:07:00 by sjolliet         ###   ########.fr       */
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

typedef struct s_exec_data
{
	char	**paths;
	char	**cmd;
	char	*full_path;
	char	*j_cmd;
}			t_exec_data;

void	throw_error(char *err_msg, char *err_loc);
void	cleanup_and_exit(t_pipe_data *p_data, char *err_msg, char *err_loc);
void	open_files(t_pipe_data *pipes, char **argv);
void	close_fds(t_pipe_data *p_data);
void	first_child(t_pipe_data *p_data, char *cmd, char **envp);
void	second_child(t_pipe_data *p_data, char *cmd, char **envp);
void	free_char_tab(char **tab);
void	execute_cmd(t_pipe_data *p_data, char **envp, char *arg);
void	free_exec_data(t_exec_data *e_data);

#endif