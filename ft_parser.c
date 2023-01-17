/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:47:54 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/17 17:45:58 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

int	echo_fill(t_cmd *config, char *line, int i)
{
	int		count;
	char	*e;

	e = ft_strdup("echo");
	count = 0;
	while (line[0] != ' ')
	{
		line++;
	}
	line++;
	config->cmd_line[i] = strdup(e);
	line = ft_strtrim(line, " ");
	if (line[count] == '-')
		line = mod_echo(line, config, i);
	else
	{
		config->cmd_args[i] = 0;
	}
	if (check_quotes(config, line, i) == 0)
		printf("errore quotes\n");
	free(e);
	return (1);
}

char	**cmd_parser(t_cmd *config)
{
	config->num_cmd = 1;
	config->parser_x = 0;
	config->parser_o = 0;
	config->n_parser = 0;
	parser_count(config);
	config->cmd_parser = malloc(sizeof(char *) * (config->num_cmd + 1));
	config->parser_y = 0;
	config->parser_x = 0;
	config->num_cmd = 0;
	config->parser_tmp = malloc(ft_strlen(config->line));
	find_tmp(config);
	config->cmd_parser[config->num_cmd] = ft_strtrim(config->parser_tmp, " ");
	config->cmd_parser[config->num_cmd + 1] = 0;
	config->num_cmd++;
	free(config->parser_tmp);
	return (config->cmd_parser);
}

void	cmd_fill(t_cmd *config)
{
	cmd_init(config);
	while (config->cmd_parser[config->cmd_i])
	{
		config->cmd_tmp = config->cmd_parser[config->cmd_i];
		if (config->cmd_tmp[0] == 'e' && config->cmd_tmp[1] == 'c')
		{
			echo_fill(config, config->cmd_tmp, config->cmd_i);
			config->cmd_i++;
			continue ;
		}
		config->cmd_tmp2 = ft_split(config->cmd_tmp, ' ');
		if (config->cmd_tmp2[1] == NULL)
		{
			cmd_if(config, config->cmd_tmp2);
			continue ;
		}
		config->cmd_line[config->cmd_i] = ft_strdup(config->cmd_tmp2[0]);
		if (config->cmd_tmp2[1])
			config->cmd_args[config->cmd_i] = ft_strdup(config->cmd_tmp2[1]);
		if (config->cmd_tmp2[2])
			config->cmd_value[config->cmd_i] = ft_strdup(config->cmd_tmp2[2]);
		config->cmd_i++;
		free_matrix (config->cmd_tmp2);
	}
	null_space(config);
}
