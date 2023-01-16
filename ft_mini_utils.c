/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:44:40 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 16:57:50 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_execute(t_cmd *config)
{
	if (config->red == 1)
		return (single_right(config));
	if (config->red == 2)
		return (double_right(config));
	if (config->red == 3)
		return (single_left(config));
	if (config->red == 4)
		return (double_left(config));
	return (0);
}

int	else_execute(t_cmd *config)
{
	if (config->red == 1)
		return (single_right(config));
	if (config->red == 2)
		return (double_right(config));
	if (config->red == 3)
		return (single_left(config));
	if (config->red == 4)
		return (double_left(config));
	return (0);
}

int	cmd_execute(t_cmd *config)
{
	if (config->npipe > 0)
	{
		if (config->red > 0)
			if_execute (config);
		else
			return (pipe_execute(config));
	}
	else
	{
		if (config->red > 0)
			else_execute(config);
		else
			return (cmd_single(config));
	}
	return (0);
}

int	cmd_prepare(t_cmd *config)
{
	int	i;

	i = 0;
	if (config->cmd_line[0] == NULL)
	{
		return (1);
	}
	while (i < config->builtin_len)
	{
		if (ft_strcmp(config->cmd_line[0], config->builtin_cmd[i]) == 0)
		{
			return (builtin_func(config->builtin_cmd[i],
					&config->cmd_args[0], config));
		}
		i++;
	}
	return (cmd_execute(config));
}

char	**ft_set_envp(char **envp)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = malloc((ft_matrix_len(envp) + 2) * 8);
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = 0;
	return (env_copy);
}
