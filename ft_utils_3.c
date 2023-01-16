/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:17:51 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 20:40:12 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_space(t_cmd *config)
{
	config->cmd_line[config->cmd_i] = NULL;
	config->cmd_args[config->cmd_i] = NULL;
	config->cmd_value[config->cmd_i] = NULL;
}

void	cmd_init(t_cmd *config)
{
	config->cmd_i = 0;
	config->cmd_line = malloc(1000);
	config->cmd_args = malloc(1000);
	config->cmd_value = malloc(1000);
}

void	parser_count(t_cmd *config)
{
	while (config->line[config->parser_x])
	{
		while (config->parser_o < 3)
		{
			if (config->line[config->parser_x] == config->index_q[0])
				config->n_parser++;
			if (config->line[config->parser_x]
				== config->operator[config->parser_o]
				&& (config->n_parser % 2) == 0)
				count_if(config);
			config->parser_o++;
		}
		config->parser_o = 0;
		config->parser_x++;
	}
}

void	count_if(t_cmd *config)
{
	config->num_cmd++;
	if (config->line[config->parser_x] == config->operator[0])
		config->npipe++;
	if (config->line[config->parser_x] == config->operator[1])
	{
		config->red = 1;
		if (config->line[config->parser_x - 1] == config->operator[1])
			config->red = 2;
	}
	if (config->line[config->parser_x] == config->operator[2])
	{
		config->red = 3;
		if (config->line[config->parser_x - 1] == config->operator[2])
			config->red = 4;
	}
}

char	*find_tmp(t_cmd *config)
{
	while (config->line[config->parser_x])
	{
		while_tmp(config);
		config->parser_tmp[config->parser_y] = config->line[config->parser_x];
		config->parser_y++;
		config->parser_x++;
		config->parser_o = 0;
	}
	config->parser_tmp[config->parser_y] = '\0';
	return (config->parser_tmp);
}
