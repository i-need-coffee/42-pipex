/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/12 15:52:58 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	char	**paths;
	char	*path_str;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	free(path_str);
	return (paths);
}

void	free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	execute_cmd(t_pipe_data *p_data, char **envp, char *arg)
{
	/* 	char *args[] = {"/usr/bin/wc", "-w", NULL};
	execve("/usr/bin/wc", args, envp); */
	char	**paths;
	char	**split_arg;
	char	*cmd;
	char	*full_path;
	int		i;
	char	*err_msg;

	paths = get_paths(envp);
	if (!paths)
		cleanup_and_exit(&p_data, "Problem with retrieving paths");
	split_arg = ft_split(arg, ' ');
	if (!split_arg)
	{
		free_char_tab(paths);
		cleanup_and_exit(&p_data, "Memory allocation failed");
	}
	cmd = ft_strjoin("/", split_arg[0]);
	if (!cmd)
	{
		free_char_tab(paths);
		free_char_tab(split_arg);
		cleanup_and_exit(&p_data, "Memory allocation failed");
	}
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!full_path)
		{
			free_char_tab(paths);
			free_char_tab(split_arg);
			free(cmd);
			cleanup_and_exit(&p_data, "Memory allocation failed");
		}
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		i++;
	}
	free_char_tab(paths);
	free_char_tab(split_arg);
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	p_data;

	ft_memset(&p_data, -1, sizeof(p_data));
	if (argc != 5)
		cleanup_and_exit(&p_data, "Program needs 4 arguments");
	open_files(&p_data, argv);
	if (pipe(p_data.fds) == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	p_data.pid1 = fork();
	if (p_data.pid1 == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	if (p_data.pid1 == 0)
		first_child(&p_data, argv[2], envp);
	p_data.pid2 = fork();
	if (p_data.pid2 == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	if (p_data.pid2 == 0)
		second_child(&p_data, argv[3], envp);
	close_fds(&p_data);
	if (waitpid(p_data.pid1, NULL, 0) == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	if (waitpid(p_data.pid2, NULL, 0) == -1)
		cleanup_and_exit(&p_data, strerror(errno));
	return (0);
}
