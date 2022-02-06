/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:13:41 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 13:15:53 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_commands(t_lxr *lxr, int pos, int ret)
{
	t_lxr	*tmp;

	tmp = lxr;
	tmp = move_tmp(tmp, pos);
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT
			|| tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
		}
		else if ((tmp->token == WORD || tmp->token == SQUOTE
				|| tmp->token == DQUOTE) && tmp->value)
		{
			ret++;
			while (tmp->next->token == WORD || tmp->next->token == SQUOTE
				|| tmp->next->token == DQUOTE)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (ret);
}

char	**find_cmds_cont(t_lxr **tmp, char **cmds, int *i)
{
	cmds[*i] = ft_strdup((*tmp)->value);
	while ((*tmp)->next->token == WORD || (*tmp)->next->token == SQUOTE
		|| (*tmp)->next->token == DQUOTE)
	{
		(*tmp) = (*tmp)->next;
		cmds[*i] = ft_strjoin_utils_echo(cmds[*i], (*tmp)->value);
	}
	*i += 1;
	return (cmds);
}

char	**find_commands(t_lxr *tmp, char **cmds, int *i)
{
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT
			|| tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
		}
		else if ((tmp->token == WORD || tmp->token == SQUOTE
				|| tmp->token == DQUOTE) && tmp->value)
			cmds = find_cmds_cont(&tmp, cmds, i);
		tmp = tmp->next;
	}
	return (cmds);
}

char	**parse_commands(int nb_cmds, t_lxr *lxr, int pos)
{
	int		i;
	char	**cmds;
	t_lxr	*tmp;

	i = 0;
	tmp = lxr;
	cmds = malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	tmp = move_tmp(tmp, pos);
	find_commands(tmp, cmds, &i);
	cmds[i] = '\0';
	return (cmds);
}
