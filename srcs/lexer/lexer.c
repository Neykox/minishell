/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:46 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/01 17:22:12 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr	*is_dredir_quote_space(t_lxr *tmp, char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tmp->token = DREDIR_LEFT;
		tmp->value = ft_strdup("<<");
		*i += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tmp->token = DREDIR_RIGHT;
		tmp->value = ft_strdup(">>");
		*i += 2;
	}
	else if (line[*i] == '\'')
		tmp = check_quote(tmp, line, i, '\'');
	else if (line[*i] == '"')
		tmp = check_quote(tmp, line, i, '"');
	else if (line[*i] == ' ')
	{
		tmp->token = WSPACE;
		tmp->value = ft_strdup(" ");
		while (line[*i] == ' ')
			*i += 1;
	}
	return (tmp);
}

t_lxr	*is_notop_pipe_redir(t_lxr *tmp, char *line, int *i)
{
	if (ft_notop(line[*i]))
		tmp = check_notop(tmp, line, i);
	else if (line[*i] == '|')
	{
		tmp->token = PIPE;
		tmp->value = ft_strdup("|");
		*i += 1;
	}
	else if (line[*i] == '<' && line[*i + 1] != '<')
	{
		tmp->token = REDIR_STDIN;
		tmp->value = ft_strdup("<");
		*i += 1;
	}
	else if (line[*i] == '>' && line[*i + 1] != '>')
	{
		tmp->token = REDIR_STDOUT;
		tmp->value = ft_strdup(">");
		*i += 1;
	}
	else
		tmp = is_dredir_quote_space(tmp, line, i);
	return (tmp);
}

t_lxr	*tokenize(t_lxr *lexer, char *line, int *i)
{
	t_lxr	*tmp;

	tmp = malloc(sizeof(t_lxr));
	if (!tmp)
		return (NULL);
	tmp = is_notop_pipe_redir(tmp, line, i);
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	build_lxr(&lexer, tmp);
	return (lexer);
}

t_lxr	*lexer(t_lxr *lexer, char *line)
{
	int		i;

	i = 0;
	if (!line[i])
		lexer = tokenize(lexer, line, &i);
	while (line[i])
	{
		lexer = tokenize(lexer, line, &i);
		if (lexer == NULL)
			break ;
	}
	if (lexer == NULL)
		return (NULL);
	lexer = append_end(lexer);
	return (lexer);
}
