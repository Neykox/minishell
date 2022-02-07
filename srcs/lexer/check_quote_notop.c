/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_notop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:19:27 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 15:36:37 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_buffer(char *line, int j)
{
	int	buffer;

	buffer = 0;
	while (line[j] != '|' && line[j] != '<' && line[j] != '>' && line[j] != ' '
		&& line[j] != '\'' && line[j] != '"' && line[j])
	{
		j++;
		buffer++;
	}
	return (buffer);
}

t_lxr	*copy_value(t_lxr *tmp, char *line, int *i, char quote)
{
	int	k;

	k = 0;
	if (line[*i + 1] == quote)
		*i += 2;
	else
	{
		*i += 1;
		while (line[*i] && line[*i] != quote)
		{
			tmp->value[k] = line[*i];
			k++;
			*i += 1;
		}
		if (line[*i])
			*i += 1;
	}
	tmp->value[k] = '\0';
	return (tmp);
}

t_lxr	*check_quote(t_lxr *tmp, char *line, int *i, char quote)
{
	int	j;
	int	k;

	j = *i;
	if (quote == '\'')
		tmp->token = SQUOTE;
	else
		tmp->token = DQUOTE;
	k = 0;
	k = verify_quote(line, j, k, quote);
	if (k == -1)
	{
		k = malloc_quote(line, j, k, quote);
		tmp->token = QUOTE_ERROR;
	}
	tmp->value = malloc(sizeof(char *) * (k + 1));
	if (!(tmp->value))
		return (NULL);
	tmp = copy_value(tmp, line, i, quote);
	return (tmp);
}

t_lxr	*check_notop(t_lxr *tmp, char *line, int *i)
{
	int	j;
	int	k;

	tmp->token = WORD;
	j = *i;
	k = count_buffer(line, j);
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
