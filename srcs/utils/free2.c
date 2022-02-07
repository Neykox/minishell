/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:52:51 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 21:26:08 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		free(pipefd[i]);
		i++;
	}
	if (nb_pipe)
		free(pipefd);
}

t_lxr	*free_lxr(t_lxr *lxr)
{
	t_lxr	*tmp;
	t_lxr	*node;

	node = lxr;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	lxr = NULL;
	return (lxr);
}

t_redir	*free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*node;

	node = redir;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (tmp->redir)
			free(tmp->redir);
		free(tmp);
	}
	redir = NULL;
	return (redir);
}
