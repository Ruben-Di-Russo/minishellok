/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:09 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 15:12:24 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char **args)
{
	if (args[0] == NULL)
	{
		fprintf(stderr, "expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[0]) != 0)
			perror("shell");
	}
	return (1);
}

int	cmd_exit(char **args, t_cmd *config)
{
	ft_clean(config);
	free_matrix(config->envp);
	free_matrix(config->builtin_cmd);
	free(config->operator);
	free(config->index_q);
	if (args[0])
		exit(ft_atoi(args[0]));
	exit(0);
}

int	cmd_unset(char **args, t_cmd *config)
{
	return (ft_unset(args, config));
}

char	*operator(void)
{
	char	*op;

	op = malloc(sizeof(char) * 3 + 1);
	op[0] = '|';
	op[1] = '>';
	op[2] = '<';
	op[3] = '\0';
	return (op);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 - *s2 == 0)
		{
			s1++;
			s2++;
		}
		else
		{
			return (*s1 - *s2);
		}
	}
	return (*s1 - *s2);
}
