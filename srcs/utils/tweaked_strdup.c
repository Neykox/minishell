/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tweaked_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <nel-masr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:18:15 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 20:22:26 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	move_i(const char *s)
{
	int	j;
	int	i;

	j = 0;
	while (s[j])
	{
		if (s[j] != '.' && s[j] != '/')
			i++;
		j++;
	}
	return (i);
}

char	*tweaked_strdup(const char *s)
{
	int		i;
	int		j;
	char	*target;

	i = 0;
	i = move_i(s);
	target = malloc((i + 1) * sizeof(char));
	if (!target)
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
