/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/14 16:12:38 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsing_error(t_lxr *lxr, int ret)
{
	if (ret == 1)
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, &(lxr->next->value), ft_strlen(lxr->next->value));
		write(2, "\n", 1);
		printf("'%s'\n", lxr->next->value);
	}
	if (ret == 2)
		write(2, "minishell: syntax error: uneven number of quotes\n", 49);
	if (ret == 3)
		write(2, "minishell: failed allocating proper memory for token values\n", 60);
}

int	syntax_checker(t_lxr *lxr)
{
	t_lxr*	parser;

	if (!lxr)
		return (3);
	parser = lxr;
	if (parser->token == PIPE)
		return (1);
	while (1)
	{
		if (!parser)
			return (0);
		if (parser->next)
		{
			if (parser->token == PIPE && parser->next->token != WORD)
				return (1);
			if (parser->token == REDIR_STDIN && parser->next->token != WORD)
				return (1);
			if (parser->token == REDIR_STDOUT && parser->next->token != WORD)
				return (1);
			if (parser->token == DREDIR_LEFT && parser->next->token != WORD)
				return (1);
			if (parser->token == DREDIR_RIGHT && parser->next->token != WORD)
				return (1);
			if (parser->token == QUOTE_ERROR)
				return (2);
			/*if (parser->token == DQUOTE)
				if (verify_quote(line, -1, 0, '"') == -1)
					return (2);*/
}
		parser = parser->next;
	}
}

int	parser(t_lxr *lxr)
{
	int	ret;

	ret = syntax_checker(lxr);
	if (ret != 0)
		print_parsing_error(lxr, ret);
	return (ret);
}
