/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:16:51 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 17:02:15 by rdi-russ         ###   ########.fr       */
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
