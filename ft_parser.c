/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:47:54 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 16:48:20 by rdi-russ         ###   ########.fr       */
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
	char	*value;

	value = ft_strdup("-n");
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
	{
		line++;
		line++;
		line++;
		config->cmd_args[i] = strdup(value);
		line = ft_strtrim(line, " ");
	}
	else
	{
		config->cmd_args[i] = 0;
	}
	if (check_quotes(config, line, i) == 0)
		printf("errore quotes\n");
	free(e);
	free(value);
	return (1);
}

char	**cmd_parser(t_cmd *config)
{
	char	*tmp;
	int		x;
	int		y;
	int		o;
	int		n;

	config->num_cmd = 1;
	x = 0;
	o = 0;
	n = 0;
	while (config->line[x])
	{
		while (o < 3)
		{
			if (config->line[x] == config->index_q[0])
				n++;
			if (config->line[x] == config->operator[o] && (n % 2) == 0)
			{
				config->num_cmd++;
				if (config->line[x] == config->operator[0])
					config->npipe++;
				if (config->line[x] == config->operator[1])
				{
					config->red = 1;
					if (config->line[x - 1] == config->operator[1])
						config->red = 2;
				}
				if (config->line[x] == config->operator[2])
				{
					config->red = 3;
					if (config->line[x - 1] == config->operator[2])
						config->red = 4;
				}
			}
			o++;
		}
		o = 0;
		x++;
	}
	config->cmd_parser = malloc(sizeof(char *) * (config->num_cmd + 1));
	y = 0;
	x = 0;
	config->num_cmd = 0;
	tmp = malloc(ft_strlen(config->line));
	while (config->line[x])
	{
		while (o < 3)
		{
			if (config->line[x] == config->index_q[0])
				n++;
			if (config->line[x] == config->operator[o] && (n % 2) == 0)
			{
				if (config->line[x + 1] == config->operator[o])
					x++;
				tmp[y] = '\0';
				config->cmd_parser[config->num_cmd] = ft_strtrim(tmp, " ");
				config->num_cmd++;
				x++;
				y = 0;
				continue ;
			}
			o++;
		}
		tmp[y] = config->line[x];
		y++;
		x++;
		o = 0;
	}
	tmp[y] = '\0';
	config->cmd_parser[config->num_cmd] = ft_strtrim(tmp, " ");
	config->cmd_parser[config->num_cmd + 1] = 0;
	config->num_cmd++;
	free (tmp);
	return (config->cmd_parser);
}

void	cmd_fill(t_cmd *config)
{
	char	*tmp;
	char	**tmp2;
	int		i;
	int		x;
	int		y;

	y = 0;
	x = 0;
	i = 0;
	config->cmd_line = malloc(10000);
	config->cmd_args = malloc(10000);
	config->cmd_value = malloc(10000);
	while (config->cmd_parser[i])
	{
		tmp = config->cmd_parser[i];
		if (tmp[0] == 'e' && tmp[1] == 'c')
		{
			echo_fill(config, tmp, i);
			i++;
			continue ;
		}
		tmp2 = ft_split(tmp, ' ');
		if (tmp2[1] == NULL)
		{
			config->cmd_line[i] = ft_strdup(tmp2[0]);
			config->cmd_args[i] = ft_strdup("NULLO");
			config->cmd_value[i] = ft_strdup("NULLO");
			i++;
			free_matrix(tmp2);
			continue ;
		}
		config->cmd_line[i] = ft_strdup(tmp2[0]);
		if (tmp2[1])
			config->cmd_args[i] = ft_strdup(tmp2[1]);
		if (tmp2[2])
			config->cmd_value[i] = ft_strdup(tmp2[2]);
		i++;
		free_matrix(tmp2);
	}
		config->cmd_line[i] = NULL;
		config->cmd_args[i] = NULL;
		config->cmd_value[i] = NULL;
}
