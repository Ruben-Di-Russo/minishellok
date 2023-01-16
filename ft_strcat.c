/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:14:24 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 15:14:35 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	counter;

	counter = 0;
	while (dest[counter] != '\0' )
	{
		counter++;
	}
	while (*src != '\0')
	{
		dest[counter] = *src;
		src++;
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}
