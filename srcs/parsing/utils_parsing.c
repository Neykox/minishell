/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:49:44 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/13 18:44:32 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_lxr(t_lxr **lxr, t_lxr *tmp)
{
	t_lxr   *last;

	if (!(*lxr))
	{
		*lxr = tmp;
		return ;
	}
	last = *lxr;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

/*int	verify_quote(char *line, int j, int k, char quote)
{
	int pre_quotes;
	int post_quotes;

	pre_quotes = 0;
	post_quotes = 0;
	while (line[++j] == quote)
	{
		pre_quotes++;
		if (line[j + 1] == '\0')
		{
			if (pre_quotes % 2 != 0)
				return (-1);
		}
	}
	while (line[++j] != quote && line[j])
		k++;
	while (line[++j] == quote)
		post_quotes++;
	if (post_quotes != pre_quotes)
		return (-1);
	return (k);
}*/

int	verify_quote(char *line, int j, int k, char quote)
{
	j++;
	while (line[j] != quote)
	{
		k++;
		j++;
	}
	if (!(line[j]))
		return (-1);
	return (k);
}
