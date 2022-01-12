/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/12 18:28:32 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_checker(t_lxr *lxr)
{
	t_lxr*	parser;

	parser = lxr;
	while (1)
	{
		if (!parser)
			return (0);
		if (parser->token != WORD && parser->next->token == PIPE)
			return (1)
		if (parser->token == PIPE && parser->next->token != WORD)
			return (1);
		parser = parser->next;
	}
}

int	parser(t_lxr *lxr)
{
	int	ret;

	ret = syntax_checker(lxr);
	if (ret != 0)
		print_parsing_error(lxr, ret);
}
