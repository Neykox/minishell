/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tweaked_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <nel-masr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:18:15 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/25 16:28:29 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tweaked_strdup(const char *s)
{
	int		i;
	int		j;
	char	*target;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != '.' && s[j] != '/')
			i++;
		j++;
	}
	if (!(target = malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != '.' && s[j] != '/')
		{
			target[i] = s[j];
			i++;
		}
		j++;
	}
	target[i] = '\0';
	return (target);
}
