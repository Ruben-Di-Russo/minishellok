/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:17:20 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 15:21:18 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	size_t	c;
	int		s;
	int		res;

	c = 0;
	s = 1;
	res = 0;
	while ((str[c] >= 9 && str[c] <= 13) || str[c] == 32)
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (str[c] - '0') + (res * 10);
		c++;
	}
	return (res * s);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isprint(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	cmd_single(t_cmd *config)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_check(config))
		{
			printf("error exec.\n");
		}
		return (1);
	}
	else
	{
		waitpid(-1, NULL, 0);
	}
	return (2);
}

void	ft_checkunset(t_cmd *config, char *str)
{
	int	i;

	i = -1;
	while (config->envp[++i])
	{
		if (ft_strncmp(config->envp[i], str, ft_strlen(str)) == 0)
		{
			free(config->envp[i]);
			while (config->envp[i + 1])
			{
				config->envp[i] = config->envp[i + 1];
				i++;
			}
			config->envp[i] = 0;
		}
	}
}
