/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:46 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/11 12:28:28 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr	*check_dquote(t_lxr *tmp, char *line, int *i)
{
	
}

t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote)
{
	int j;
	int k;
	int	pre_quotes;
	int	post_quotes;

	if (quote = ''')
		tmp->token = SQUOTE;
	else
		tmp->token = DQUOTE;
	j = i - 1;
	if ((k = verify_squote(line, j, k, quote)) == -1)
		k = 0;
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	k = 0;
	while (line[++j] != quote)
	{
		tmp->value[k] = line[j];
		k++;
		*i += 1;
	}
	tmp->value[k] = '\0';
	return (tmp);
}

t_lxr	*check_alnum(t_lxr *tmp, char *line, int *i)
{
	int	j;
	int	k;

	tmp->token = WORD;
	j = i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ')
	{
		j++;
		k++;
	}
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	j = i;
	k = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' ')
	{
		tmp->value[k] = line[j];
		j++;
		k++;
		*i += 1;
	}
	tmp->value[k] = '\0';
	return (tmp);
}

t_lxr	*lexer(t_lxr *lexer, char *line)
{
	int		i;
	t_lxr	*tmp;

	while (line[i])
	{
		if (ft_isalnum(line[i]))
			tmp = check_alnum(tmp, line, &i);
		else if (line[i] == '|')
		{
			tmp->token = PIPE;
			tmp->value = ft_strdup("|");
			i++;
		}
		else if (line[i] == '<' && line[i + 1] != '<')
		{
			tmp->token = REDIR_LEFT;
			tmp->value = ft_strdup("<");
			i++;
		}
		else if (line[i] == '>' && line[i + 1] != '>')
		{
			tmp->token = REDIR_RIGHT;
			tmp->value = ft_strdup(">");
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			tmp->token = DREDIR_LEFT;
			tmp->value = ft_strdup("<<");
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			tmp->token = DREDIR_RIGHT;
			tmp->value = ft_strdup(">>");
			i += 2;
		}
		else if (line[i] == ''')
			tmp = check_squote(tmp, line, &i);
		else if (line[i] == '"')
			tmp = check_dquote(tmp, line, &i);
		else
			i++;
		build_lxr(&lexer, tmp);
	}
}
