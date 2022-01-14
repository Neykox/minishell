/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:46 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/14 15:20:34 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr	*append_end(t_lxr *lexer)
{
	t_lxr	*tmp;

	tmp = malloc(sizeof(t_lxr));
	tmp->token = END;
	tmp->value = ft_strdup("\\n");
	tmp->next = NULL;
	build_lxr(&lexer, tmp);
	return (lexer);
}

t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote)
{
	int	j;
	int k;

	j = *i;
	if (quote == '\'')
		tmp->token = SQUOTE;
	else
		tmp->token = DQUOTE;
	k = 0;
	k = verify_quote(line, j, k, quote);
	if (k == -1)
	{
		k = 0;
		tmp->token = QUOTE_ERROR;;
	}
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	k = 0;
	if (line[*i + 1] == quote)
		*i += 2;
	else
	{
		*i += 1;
		while (line[*i] != quote && line[*i])
		{
			tmp->value[k] = line[*i];
			k++;
			*i += 1;
		}
		*i += 1;
	}
	tmp->value[k] = '\0';
	return (tmp);
}

t_lxr	*check_notop(t_lxr *tmp, char *line, int *i)
{
	int	j;
	int	k;

	tmp->token = WORD;
	j = *i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ' 
					&& line[j] != '\'' && line[j] != '"' && line[j])
	{
		j++;
		k++;
	}
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	j = *i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ' 
					&& line[j] != '\'' && line[j] != '"' && line[j])
	{
		tmp->value[k] = line[j];
		j++;
		k++;
		*i += 1;
	}
	tmp->value[k] = '\0';
	return (tmp);
}

t_lxr	*tokenize(t_lxr *lexer, char *line, int *i)
{
	t_lxr	*tmp;

	tmp = malloc(sizeof(t_lxr));
	if (!tmp)
		return (NULL);
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
	else if (line[*i] == '<' && line[*i + 1] == '<')
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
		/*while (line[i] == ' ')
			i++;*/
	}
	if (lexer == NULL)
		return (NULL);
	lexer = append_end(lexer);
	return (lexer);
}
