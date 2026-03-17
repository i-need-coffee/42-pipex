/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:01:32 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/17 22:19:28 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <libft.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_pipe_data
{
	int		num_cmds;
	int		**pipes;
	int		p_count;
	pid_t	*pids;
	int		fd_in;
	int		fd_out;
}			t_pipe_data;

typedef struct s_exec_data
{
	char	**paths;
	char	**args;
	char	*full_path;
	char	*j_cmd;
}			t_exec_data;

void	throw_error(char *err_msg, char *err_loc);
void	cleanup_and_exit(t_pipe_data *p_data, char *err_msg, char *err_loc);
void	open_files(t_pipe_data *p_data, char **argv, int argc);
void	close_fds(t_pipe_data *p_data);
void	free_char_tab(char **tab);
void	execute_cmd(t_pipe_data *p_data, char **envp, char *cmd);
void	free_exec_data(t_exec_data *e_data);
char	**create_args(char *cmd);
void	free_args(char **args, int count);
void	create_pipes(t_pipe_data *p_data);
void	free_pipe_data(t_pipe_data *p_data);
void	init_pipe_data(t_pipe_data *p_data);
void	create_children(t_pipe_data *p_data, char **argv, char **envp);

#endif