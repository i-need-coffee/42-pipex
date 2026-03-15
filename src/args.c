/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:24:05 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/15 19:58:15 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_args(char *cmd);
static int	fill_args(char **args, char *cmd);
static int	get_arg_len(char *cmd);
static char	*substr_arg(char *cmd, int len);

char	**create_args(char *cmd)
{
	char	**args;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isspace(cmd[i]) || cmd[i] == '\'')
			i++;
		else
			break ;
	}
	if (!cmd || cmd[i] == '\0')
		return (NULL);
	args = (char **)malloc((count_args(cmd) + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	if (!fill_args(args, cmd))
		return (NULL);
	return (args);
}

static int	count_args(char *cmd)
{
	int	count;
	int	i;
	int	is_arg;

	count = 0;
	i = 0;
	is_arg = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && !is_arg)
		{
			count++;
			is_arg = 1;
			if (cmd[i] == '\'')
			{
				i++;
				while (cmd[i] && cmd[i] != '\'')
					i++;
			}
		}
		else if (cmd[i] == ' ')
			is_arg = 0;
		i++;
	}
	return (count);
}

static int	fill_args(char **args, char *cmd)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (!cmd[i])
			break ;
		len = get_arg_len(cmd + i);
		args[j] = substr_arg(cmd + i, len);
		if (!args[j])
		{
			free_args(args, j);
			return (0);
		}
		i += len;
		j++;
	}
	args[j] = NULL;
	return (1);
}

static int	get_arg_len(char *cmd)
{
	int	len;
	int	in_quotes;

	len = 0;
	in_quotes = 0;
	while (cmd[len])
	{
		if (cmd[len] == '\'')
			in_quotes = !in_quotes;
		else if (cmd[len] == ' ' && !in_quotes)
			break ;
		len++;
	}
	return (len);
}

static char	*substr_arg(char *cmd, int len)
{
	char	*arg;
	int		i;
	int		j;

	arg = malloc((len + 1) * sizeof(char));
	if (!arg)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (cmd[i] != '\'')
		{
			arg[j] = cmd[i];
			j++;
		}
		i++;
	}
	arg[j] = '\0';
	return (arg);
}
