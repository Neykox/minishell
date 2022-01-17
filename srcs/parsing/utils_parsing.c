/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:49:44 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/17 14:11:11 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_lxr(t_lxr **lxr, t_lxr *tmp)
{
	t_lxr	*last;

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

t_lxr	*append_end(t_lxr *lexer)
{
	t_lxr	*tmp;

	tmp = malloc(sizeof(t_lxr));
	tmp->token = END;
	tmp->value = ft_strdup("newline");
	tmp->next = NULL;
	build_lxr(&lexer, tmp);
	return (lexer);
}

int	verify_quote(char *line, int j, int k, char quote)
{
	j++;
	while (line[j] != quote && line[j])
	{
		k++;
		j++;
	}
	if (!(line[j]))
		return (-1);
	return (k);
}
