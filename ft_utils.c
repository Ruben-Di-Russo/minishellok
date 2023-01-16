/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:58:13 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 15:11:22 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(t_cmd *config)
{
	if (config->cmd_line[0][0] == '/')
	{
		execve(config->cmd_line[0], args_build(config, 0), config->envp);
		return (1);
	}
	else
	{
		execve(ft_pathfinder(config->cmd_line[0], config->envp),
			args_build(config, 0), config->envp);
		return (1);
	}
	return (0);
}

int	ft_check_pipe(t_cmd *config, int i)
{
	if (config->cmd_line[i][0] == '/')
	{
		execve(config->cmd_line[i], args_build(config, i), config->envp);
		ft_free_matrix(config->arg_build);
		return (1);
	}
	else
	{
		execve(ft_pathfinder(config->cmd_line[i], config->envp),
			args_build(config, i), config->envp);
		ft_free_matrix(config->arg_build);
		return (1);
	}
	return (0);
}

char	**builtin_str(void)
{
	char	*cmd;
	char	**str;

	cmd = "cd exit export unset";
	str = ft_split(cmd, (char)SPACE_DELM);
	return (str);
}

void	ft_clean(t_cmd *config)
{
	printf("start cleaning ... \n");
	config->red = 0;
	config->npipe = 0;
	free(config->line);
	free_matrix(config->cmd_parser);
	free_matrix(config->cmd_value);
	free_matrix(config->cmd_line);
	free_matrix(config->cmd_args);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		if (matrix[i])
		{
			free(matrix[i]);
		}
		i++;
	}
}
