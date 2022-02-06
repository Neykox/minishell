/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:45:57 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 18:49:28 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(t_exec *exec)
{
	int	k;

	k = 0;
	if (!exec->save)
	{
		while (k < exec->nb_pipe)
		{
			close(exec->pipefd[k][0]);
			close(exec->pipefd[k][1]);
			k++;
		}
	}
	else
	{
		while (k < exec->save)
		{
			close(exec->pipefd[k][0]);
			close(exec->pipefd[k][1]);
			k++;
		}
	}
}

void	close_fds(t_exec *exec)
{
	int	i;

	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].redir != NULL)
			close_redir_fd(exec->pipes[i].redir);
		i++;
	}
}
