/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:21:32 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 17:27:51 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar(char *line, int time, t_cmd *config)
{
	char	**tmp;
	char	*mat;
	int		try;

	tmp = ft_split(line, ' ');
	try = 0;
	config->find_x = 0;
	while (tmp[config->find_x])
	{
		if (ft_strchr(tmp[config->find_x], '$'))
			tmp[config->find_x] = ft_strchr(tmp[config->find_x], '$');
		mat = ft_strtrim(tmp[config->find_x], "\", \'");
		config->jump = ft_strlen(mat);
		if (mat[config->find_x] == '$')
		{
			if (try == time)
			{
				free_matrix(tmp);
				return (mat);
			}
			try++;
		}
		config->find_x++;
	}
	return (NULL);
}

char	*find_envp(t_cmd *config, char *tmp)
{
	char	*dollaro;
	char	**dollarofinito;
	int		x;

	x = 0;
	dollaro = NULL;
	while (config->envp[x])
	{
		if (ft_strncmp(config->envp[x], tmp, ft_strlen(tmp)) == 0)
		{
			dollarofinito = ft_split(config->envp[x], '=');
			dollaro = ft_strdup(dollarofinito[1]);
			free_matrix(dollarofinito);
			free(tmp);
			return (dollaro);
		}
		x++;
	}
	return (dollaro);
}

char	*dollar(t_cmd *config, char *line, int time)
{
	int	x;

	x = 0;
	config->dollar_tmp2 = find_dollar(line, time, config);
	if (!config->dollar_tmp2)
		return (NULL);
	config->dollar_tmp = ft_strtrim(config->dollar_tmp2, "$");
	free(config->dollar_tmp2);
	if (config->dollar_tmp[x] == '?')
	{
		config->jump = 2;
		free(config->dollar_tmp);
		config->dollar_tmp = ft_strdup(config->exit_code);
		return (config->dollar_tmp);
	}
	while (config->dollar_tmp[x] != '\0')
	{
		if (!(config->dollar_tmp[x] >= 65 && config->dollar_tmp[x] <= 90))
			return (NULL);
		x++;
	}
	config->dollar_tmp = find_envp(config, config->dollar_tmp);
	if (!config->dollar_tmp)
		return (NULL);
	return (config->dollar_tmp);
}
