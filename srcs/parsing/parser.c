/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/18 17:24:43 by nel-masr         ###   ########.fr       */
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

int	syntax_checker(t_lxr *lxr)
{
	t_lxr	*parser;

	if (!lxr)
		return (3);
	parser = lxr;
	if (parser->token == PIPE)
	{
		if (parser->next->token != WSPACE)
			print_parsing_error(parser->next->value, 1);
		else
			print_parsing_error(parser->next->next->value, 1);
		return (1);
	}
	while (1)
	{
		if (!parser)
			return (0);
		if (parser->token == QUOTE_ERROR)
			return (2);
		if (parser->token == WSPACE || parser->token == WORD || parser->token == END
			|| parser->token == SQUOTE || parser->token == DQUOTE)
			parser = parser->next;
		else if (parser->token == REDIR_STDIN || parser->token == REDIR_STDOUT
			|| parser->token == DREDIR_LEFT || parser->token == DREDIR_RIGHT)
		{
			parser = parser->next;
			if (parser->token == WSPACE)
				parser = parser->next;
			if (parser->token == QUOTE_ERROR)
				return (2);
			else if (parser->token != WORD && parser->token != SQUOTE && 
				parser->token != DQUOTE)
			{
				print_parsing_error(parser->value, 1);
				return (1);
			}
		}
		else if (parser->token == PIPE)
		{
			parser = parser->next;
			if (parser->token == WSPACE)
				
					parser = parser->next;
			if (parser->token == QUOTE_ERROR)
				return (2);
			else if (parser->token == END)
			{
				print_parsing_error(parser->value, 1);
				return (1);
			}
		}
	}
}

int	count_pipes(t_lxr *lxr)
{
	int		i;
	t_lxr	*tmp;

	i = 0;
	tmp = lxr;
	while (1)
	{
		if (tmp->token == END)
			return (i);
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			i++;
			tmp = tmp->next;
		}
	}
}

int	parse_values(t_lxr *lxr, t_exec *exec)
{
	int	i;
	t_lxr	*parser;
	t_lxr	*tmp;

	i = 0;
	parser = lxr;
	tmp = lxr;
	//exec = malloc(sizeof(t_exec));
	//if (!(exec))
	//	return (3);
	exec->nb_pipe = count_pipes(lxr);
	if (exec->nb_pipe != 0)
	{
		exec->pipe_content = malloc(sizeof(char *) * ((exec->nb_pipe + 1) + 1));
		if (!(exec->pipe_content))
			return (3);
	}
	while (1)
	{
		if (!parser)
			break ;
		if (parser->token != PIPE && parser->token != END)
			parser = parser->next;
		else if (parser->token == PIPE || parser->token == END)
		{
			//exec->nb_pipe++;
			while (tmp->token != PIPE && tmp->token != END)
			{
				if (!exec->pipe_content)
					exec->pipe_content[i] = ft_strdup(tmp->value);
				else
					exec->pipe_content[i] = tw_strjoin(exec->pipe_content[i], tmp->value);
				tmp = tmp->next;
			}
			i++;
			tmp = tmp->next;
			parser = parser->next;
		}
	}
	return (0);
}

int	parser(t_lxr *lxr, t_exec *exec)
{
	int	ret;
	int	ret_parsing;

	ret_parsing = 0;
	ret = syntax_checker(lxr);
	if (ret == 2 || ret == 3)
		print_parsing_error(NULL, ret);
	else if (ret == 0)
		parse_values(lxr, exec);
	if (ret_parsing == 0)
		return (ret);
	else
		return (ret_parsing);
}
