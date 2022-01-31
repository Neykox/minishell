/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:07:11 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/31 18:58:08 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr	*free_lxr(t_lxr *lxr)
{
	t_lxr *tmp;
	t_lxr *node;

	node = lxr;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	lxr = NULL;
	return (lxr);
}

t_redir	*free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir *node;

	node = redir;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	redir = NULL;
	return (redir);
}

void	free_exec(t_exec *exec)
{
	int	i;
	int	j;
	int	nb_redir;

	i = 0;
	j = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].nb_cmds)
		{
			while (j < exec->pipes[i].nb_cmds)
			{
				free(exec->pipes[i].cmds[j]);
				j++;
			}
			free(exec->pipes[i].cmds);
		}
		nb_redir = exec->pipes[i].nb_redir_stdin + exec->pipes[i].nb_redir_stdout +
			exec->pipes[i].nb_dredir_right + exec->pipes[i].nb_dredir_left;
		if (nb_redir)
			exec->pipes[i].redir = free_redir(exec->pipes[i].redir);
		i++;
	}
	free(exec);
}
