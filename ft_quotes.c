/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:23:48 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/17 23:19:40 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_index(void)
{
	char	*op;

	op = malloc(sizeof(char) * 2 + 1);
	op[0] = '\"';
	op[1] = '\'';
	op[2] = '\0';
	return (op);
}

int	double_quote(t_cmd *config, char *line, int pos)
{
	int		time;
	char	*copy;

	config->echo_i = 0;
	config->echo_n = 0;
	config->echo_t = 0;
	config->echo_time = 0;
	time = 0;
	config->echo_space = 0;
	copy = malloc(ft_strlen(line) * 4);
	copy = dollar_double(config, line, copy);
	if ((config->echo_n % 2) != 0)
		return (0);
	config->cmd_value[pos] = ft_strdup(copy);
	free(copy);
	return (1);
}

int	single_quote(t_cmd *config, char *line, int pos)
{
	char	*copy;

	config->echo_i = 0;
	config->echo_n = 0;
	config->echo_t = 0;
	config->echo_space = 0;
	copy = malloc(ft_strlen(line) * 4);
	copy = single_while(config, line, copy);
	if ((config->echo_n % 2) != 0)
		return (0);
	config->cmd_value[pos] = ft_strdup(copy);
	free(copy);
	return (1);
}

int	no_quote(t_cmd *config, char *line, int pos)
{
	char	*copy;

	config->echo_i = 0;
	config->echo_space = 0;
	config->echo_t = 0;
	config->echo_time = 0;
	copy = malloc(10000);
	copy = dollar_while(config, line, copy);
	config->cmd_value[pos] = ft_strdup(copy);
	free(copy);
	return (1);
}

int	check_quotes(t_cmd *config, char *line, int pos)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == config->index_q[0])
		{
			double_quote(config, line, pos);
			free(line);
			return (1);
		}
		else if (line[i] == config->index_q[1])
		{
			single_quote(config, line, pos);
			free(line);
			return (1);
		}
		i++;
	}
	no_quote(config, line, pos);
	free(line);
	return (1);
}
