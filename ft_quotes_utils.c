/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:21:32 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 17:03:23 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar(char *line, int time, t_cmd *config)
{
	char	**tmp;
	char	*mat;
	int		try;
	int		x;

	tmp = ft_split(line, ' ');
	try = 0;
	x = 0;
	while (tmp[x])
	{
		if (ft_strchr(tmp[x], '$'))
			tmp[x] = ft_strchr(tmp[x], '$');
		mat = ft_strtrim(tmp[x], "\", \'");
		config->jump = ft_strlen(mat);
		if (mat[x] == '$')
		{
			if (try == time)
			{
				free_matrix(tmp);
				return (mat);
			}
			try++;
		}
		x++;
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
	char	*tmp;
	char	*tmp2;
	int		x;

	x = 0;
	tmp2 = find_dollar(line, time, config);
	if (!tmp2)
		return (NULL);
	tmp = ft_strtrim(tmp2, "$");
	free(tmp2);
	if (tmp[x] == '?')
	{
		config->jump = 2;
		free(tmp);
		tmp = ft_strdup(config->exit_code);
		return (tmp);
	}
	while (tmp[x] != '\0')
	{
		if (!(tmp[x] >= 65 && tmp[x] <= 90))
			return (NULL);
		x++;
	}
	tmp = find_envp(config, tmp);
	if (!tmp)
		return (NULL);
	return (tmp);
}
