/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/13 17:02:28 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsing_error(t_lxr *lxr, int ret)
{
	if (ret == 1)
		printf("minishell: syntax error near unexpected token '%s'\n",
						lxr->next->value);
	if (ret == 2)
		printf("minishell: Uneven number of quotes\n");
}

int	syntax_checker(t_lxr *lxr, char *line)
{
	t_lxr*	parser;

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
			if (parser->token == SQUOTE)
				if (verify_quote(line, -1, 0, '\'') == -1)
					return (2);
			if (parser->token == DQUOTE)
				if (verify_quote(line, -1, 0, '"') == -1)
					return (2);
}
		parser = parser->next;
	}
}

int	parser(t_lxr *lxr, char *line)
{
	int	ret;

	ret = syntax_checker(lxr, line);
	if (ret != 0)
		print_parsing_error(lxr, ret);
	return (ret);
}
