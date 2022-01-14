/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/14 16:47:05 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsing_error(t_lxr *lxr, int ret)
{
	if (ret == 1)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, lxr->next->value, ft_strlen(lxr->next->value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	if (ret == 2)
		write(2, "minishell: syntax error: uneven number of quotes\n", 49);
	if (ret == 3)
		write(2, "minishell: failed allocating proper memory for token values\n", 60);
	if (ret == 4)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, lxr->next->next->value, ft_strlen(lxr->next->value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}	
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
		/*
		 * <| for example
		 */
		if (parser->next && parser->next->token != WSPACE)
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
		}
		/*
		 * < | for example, basically we look past the WSPACE token in parser->next->next
		 */
		else if (parser->next && parser->next->next)
		{
			if (parser->next->next->token != WORD && (parser->token == PIPE ||
				parser->token == REDIR_STDIN || parser->token == REDIR_STDOUT ||
				parser->token == DREDIR_LEFT || parser->token == DREDIR_LEFT))
				return (4);
			if (parser->token == QUOTE_ERROR)
				return (2);
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
