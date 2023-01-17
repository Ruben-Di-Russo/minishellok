/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_while.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:38:42 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/17 20:38:02 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_while(t_cmd *config, char *line, char *copy)
{
	while (line[config->echo_i])
	{
		if (line[config->echo_i] == config->index_q[1])
		{
			accrocchio_1(config);
			continue ;
		}
		if ((config->echo_n % 2) == 0 && ft_isalpha(line[config->echo_i]) == 1)
		{
			copy = accrocchio_2(config, line, copy);
			continue ;
		}
		if ((config->echo_n % 2) == 0 && config->echo_space == 0)
		{
			copy = accrocchio_3(config, line, copy);
			continue ;
		}
		if ((config->echo_n % 2) == 0 && config->echo_space != 0)
		{
			accrocchio_4(config);
			continue ;
		}
		copy = accrocchio_2(config, line, copy);
	}
	return (copy);
}

void	accrocchio_1(t_cmd *config)
{
	config->echo_i++;
	config->echo_n++;
}

char	*accrocchio_2(t_cmd *config, char *line, char *tmp)
{
	config->echo_space = 0;
	tmp[config->echo_t] = line[config->echo_i];
	config->echo_i++;
	config->echo_t++;
	tmp[config->echo_t + 1] = '\0';
	return (tmp);
}

char	*accrocchio_3(t_cmd *config, char *line, char *tmp)
{
	tmp[config->echo_t] = line[config->echo_i];
	config->echo_space++;
	config->echo_i++;
	config->echo_t++;
	tmp[config->echo_t + 1] = '\0';
	return (tmp);
}

void	accrocchio_4(t_cmd *config)
{
	config->echo_space++;
	config->echo_i++;
}
