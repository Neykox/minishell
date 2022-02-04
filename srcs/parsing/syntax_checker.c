/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:00:41 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/04 12:35:58 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsing_error(char *value, int ret)
{
	if (ret == 1)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, value, ft_strlen(value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	if (ret == 2)
		write(2, "minishell: syntax error: uneven number of quotes\n", 49);
	if (ret == 3)
		write(2, "minishell: failed allocating memory for token values\n", 53);
	if (ret == 4)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, value, ft_strlen(value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}
}

int	check_redir(t_lxr **parser)
{
	*parser = (*parser)->next;
	if ((*parser)->token == WSPACE)
		*parser = (*parser)->next;
	if ((*parser)->token == QUOTE_ERROR)
		return (2);
	else if ((*parser)->token != WORD && (*parser)->token != SQUOTE
		&& (*parser)->token != DQUOTE)
	{
		print_parsing_error((*parser)->value, 1);
		return (2);
	}
	return (0);
}

int	check_pipe(t_lxr **parser)
{
	*parser = (*parser)->next;
	if ((*parser)->token == WSPACE)
		*parser = (*parser)->next;
	if ((*parser)->token == QUOTE_ERROR)
	{
		print_parsing_error(NULL, 2);
		return (2);
	}
	else if ((*parser)->token == END)
	{
		print_parsing_error((*parser)->value, 1);
		return (2);
	}
	return (0);
}

int	syntax_checker_cont(t_lxr **parser, int ret)
{
	if ((*parser)->token == QUOTE_ERROR)
	{
		print_parsing_error(NULL, 2);
		return (2);
	}
	if ((*parser)->token == WSPACE || (*parser)->token == WORD
		|| (*parser)->token == END || (*parser)->token == SQUOTE
		|| (*parser)->token == DQUOTE || (*parser)->token == VAR_ERROR)
		*parser = (*parser)->next;
	else if ((*parser)->token == REDIR_STDIN || (*parser)->token == REDIR_STDOUT
		|| (*parser)->token == DREDIR_LEFT || (*parser)->token == DREDIR_RIGHT)
	{
		ret = check_redir(parser);
		if (ret)
			return (ret);
	}
	else if ((*parser)->token == PIPE)
	{
		ret = check_pipe(parser);
		if (ret)
			return (ret);
	}
	return (0);
}

int	syntax_checker(t_lxr *lxr, t_env *new_env)
{
	t_lxr	*parser;
	int		ret;

	ret = 0;
	if (!lxr)
	{
		g_error = 2;
		if (modif_interro(new_env, ft_itoa(g_error)) == -2)
			return (-1);
		return (g_error);
	}
	parser = lxr;
	if (parser->token == PIPE)
	{
		print_parsing_error(parser->value, 1);
		g_error = 2;
		if (modif_interro(new_env, ft_itoa(g_error)) == -2)
			return (-1);
		return (g_error);
	}
	while (1)
	{
		if (!parser)
			return (0);
		else
		{
			ret = syntax_checker_cont(&parser, ret);
			if (ret)
			{
				g_error = 2;
				if (modif_interro(new_env, ft_itoa(g_error)) == -2)
					return (-1);
				return (ret);
			}
		}
	}
}
