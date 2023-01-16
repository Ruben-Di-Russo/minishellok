/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:16:51 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 18:45:00 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

int	ft_unset(char **args, t_cmd *config)
{
	char	**tmp;
	int		status;
	int		i;

	(void)args;
	tmp = ft_split(config->cmd_parser[0], ' ');
	i = 1;
	status = 0;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i][0]) && !ft_ciack(tmp[i]))
			ft_checkunset(config, tmp[i]);
		else
			status = 1;
		i++;
	}
	if (status)
		printf("errore");
	free_matrix(tmp);
	return (status);
}

char	*mod_echo(char *line, t_cmd *config, int i)
{
	char	*value;

	value = ft_strdup("-n");
	line++;
	line++;
	line++;
	config->cmd_args[i] = strdup(value);
	line = ft_strtrim(line, " ");
	free(value);
	return (line);
}

void	cmd_if(t_cmd *config, char **tmp2)
{
	config->cmd_line[config->cmd_i] = ft_strdup(tmp2[0]);
	config->cmd_args[config->cmd_i] = ft_strdup("NULLO");
	config->cmd_value[config->cmd_i] = ft_strdup("NULLO");
	free_matrix(tmp2);
	config->cmd_i++;
}
