/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:53 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/10 16:49:55 by sjolliet         ###   ########.fr       */
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

char	*get_full_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
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
	char **split = ft_split(argv[2], ' ');
	char *cmd = ft_strjoin("/", split[0]);
	char **paths = get_paths(envp);
	char *full_path = get_full_path(paths, cmd);
	ft_printf("%s\n", full_path);
/* 	char *args[] = {"/usr/bin/wc", "-w", NULL};
	execve("/usr/bin/wc", args, envp); */
	return (0);
}
