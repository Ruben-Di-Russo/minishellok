/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_while.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:34:32 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/17 22:58:05 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_while(t_cmd *config, char *line, char *copy)
{
	char	*tmp;

	config->echo_time = 0;
	while (line[config->echo_i])
	{
		if (line[config->echo_i] == '$')
		{
			tmp = dollar_put(config, config->echo_time, line);
			copy = ft_strjoin(copy, tmp);
			continue ;
		}
		if (config->echo_space == 0 && ft_isprint(line[config->echo_i]) == 0)
		{
			copy = accrocchio_3(config, line, copy);
			continue ;
		}
		if (config->echo_space != 0 && ft_isprint(line[config->echo_i]) == 0)
		{
			accrocchio_4(config);
			continue ;
		}
		copy = accrocchio_2(config, line, copy);
	}
	return (copy);
}

char	*dollar_put(t_cmd *config, int time, char *line)
{
	char	*dollaro;

	dollaro = dollar(config, line, time);
	config->echo_t = ft_strlen (dollaro);
	if (!dollaro)
		config->echo_space = 1;
	config->echo_i += config->jump;
	time++;
	config->echo_space = 0;
	return (dollaro);
}

char	*dollar_double(t_cmd *config, char *line, char *copy)
{
	while (line[config->echo_i])
	{
		if (line[config->echo_i] == '$')
		{
			copy = accrocchio_finale(config, line);
			continue ;
		}
		if (line[config->echo_i] == config->index_q[0])
		{
			accrocchio_1(config);
			continue ;
		}
		else if ((config->echo_n % 2) == 0 && config->echo_space == 0)
		{
			copy = accrocchio_3(config, line, copy);
			continue ;
		}
		else if ((config->echo_n % 2) == 0 && config->echo_space != 0)
		{
			accrocchio_4(config);
			continue ;
		}
		copy = accrocchio_2(config, line, copy);
	}
	return (copy);
}

char	*accrocchio_finale(t_cmd *config, char *line)
{
	char	*tmp;

	config->echo_tmp = dollar_put(config, config->echo_time, line);
	tmp = ft_strjoin(tmp, config->echo_tmp);
	return (tmp);
}
