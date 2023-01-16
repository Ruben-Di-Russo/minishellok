/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:02:08 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 20:40:30 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

void	while_tmp(t_cmd *config)
{
	while (config->parser_o < 3)
	{
		if (config->line[config->parser_x] == config->index_q[0])
			config->n_parser++;
		if (config->line[config->parser_x]
			== config->operator[config->parser_o]
			&& (config->n_parser % 2) == 0)
		{
			if (config->line[config->parser_x + 1]
				== config->operator[config->parser_o])
				config->parser_x++;
			config->parser_tmp[config->parser_y] = '\0';
			config->cmd_parser[config->num_cmd]
				= ft_strtrim(config->parser_tmp, " ");
			config->num_cmd++;
			config->parser_x++;
			config->parser_y = 0;
			continue ;
		}
		config->parser_o++;
	}
}
