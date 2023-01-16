/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:09 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 17:54:49 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathfinder(char *cmd, char **envp)
{
	char	**mypaths;
	char	*pathnoslash;
	char	*pathinenv;
	char	*finalpath;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	pathinenv = envp[i] + 5;
	mypaths = ft_split(pathinenv, ':');
	i = 0;
	while (mypaths[i])
	{
		pathnoslash = ft_strjoin(mypaths[i], "/");
		finalpath = ft_strjoin(pathnoslash, cmd);
		free(pathnoslash);
		if (access(finalpath, F_OK) == 0)
			return (finalpath);
		free(finalpath);
		i++;
	}
	free_matrix(mypaths);
	return (NULL);
}

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

char	*split_to_line(char **str)
{
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != NULL)
	{
		count += ft_strlen(str[i]);
		i++;
	}
	line = malloc(sizeof(char) * count + 1);
	i = 0;
	while (str[i])
	{
		ft_strcat(line, str[i]);
		i++;
	}
	line[count] = '\0';
	return (line);
}

int	len_num_builtins(char **builtin_str)
{
	int	i;

	i = 0;
	while (builtin_str[i])
	{
		i++;
	}
	return (i);
}

int	builtin_func(char *cmd, char **args, t_cmd *config)
{
	if (ft_strcmp(cmd, "cd") == 0)
	{
		return (cmd_cd(args));
	}
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(args, config));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (cmd_exit(args, config));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (cmd_unset(args, config));
	return (0);
}
