/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:19:07 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/08 14:12:56 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*find_tokens_cont(t_lxr **tmp, int *tokens, int *i)
{
	tokens[*i] = (*tmp)->token;
	while ((*tmp)->next->token == WORD || (*tmp)->next->token == SQUOTE
		|| (*tmp)->next->token == DQUOTE)
	{
		(*tmp) = (*tmp)->next;
		if (tokens[*i] == WORD && ((*tmp)->token == DQUOTE
				|| (*tmp)->token == SQUOTE))
			tokens[*i] = (*tmp)->token;
	}
	*i += 1;
	return (tokens);
}

int	*find_tokens(t_lxr *tmp, int *tokens, int *i)
{
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT
			|| tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
		}
		else if ((tmp->token == WORD || tmp->token == SQUOTE
				|| tmp->token == DQUOTE) && tmp->value)
			tokens = find_tokens_cont(&tmp, tokens, i);
		tmp = tmp->next;
	}
	return (tokens);
}

int	*parse_tokens(int nb_cmds, t_lxr *lxr, int pos)
{
	int		i;
	int		*tokens;
	t_lxr	*tmp;

	i = 0;
	tmp = lxr;
	if (!nb_cmds)
		return (0);
	tokens = malloc(sizeof(int) * (nb_cmds));
	if (!tokens)
		return (0);
	tmp = move_tmp(tmp, pos);
	find_tokens(tmp, tokens, &i);
	return (tokens);
}
