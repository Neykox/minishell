/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:46 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/11 17:15:08 by nel-masr         ###   ########.fr       */
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

t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote)
{
	int	j;
	int k;

	j = 0;
	if (quote == '\'')
		tmp->token = SQUOTE;
	else
		tmp->token = DQUOTE;
	k = 0;
	if ((k = verify_quote(line, j, k, quote)) == -1)
		k = 0;
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	k = 0;
	while (line[*i] == quote)
		*i += 1;
	while (line[*i] != quote && line[*i])
	{
		tmp->value[k] = line[*i];
		k++;
		*i += 1;
	}
	tmp->value[k] = '\0';
	while (line[*i] == quote)
		*i += 1;
	return (tmp);
}

t_lxr	*check_alnum(t_lxr *tmp, char *line, int *i)
{
	int	j;
	int	k;

	tmp->token = WORD;
	j = *i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ' && line[j])
	{
		j++;
		k++;
	}
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	j = *i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ' && line[j])
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
	if (ft_isalnum(line[*i]))
		tmp = check_alnum(tmp, line, i);
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
		i += 2;
	}
	else if (line[*i] == '\'')
		tmp = check_quote(tmp, line, i, '\'');
	else if (line[*i] == '"')
		tmp = check_quote(tmp, line, i, '"');	
	tmp->next = NULL;
	build_lxr(&lexer, tmp);
	return (lexer);
}

t_lxr	*lexer(t_lxr *lexer, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		lexer = tokenize(lexer, line, &i);
		while (line[i] == ' ')
			i++;
	}
	return (lexer);
}
