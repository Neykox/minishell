/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:07:11 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/05 20:08:42 by nel-masr         ###   ########.fr       */
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

t_env	*free_env(t_env *env)
{
	t_env *tmp;
	t_env *node;

	node = env;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (tmp->line)
			free(tmp->line);
		free(tmp);
	}
	env = NULL;
	return (env);
}

t_lxr	*free_lxr(t_lxr *lxr)
{
	t_lxr *tmp;
	t_lxr *node;

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
	t_redir *node;

	node = redir;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		if (redir->redir)
			free(redir->redir);
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
			j = 0;
			free(exec->pipes[i].cmds);
		}
		nb_redir = exec->pipes[i].nb_redir_stdin + exec->pipes[i].nb_redir_stdout +
			exec->pipes[i].nb_dredir_right + exec->pipes[i].nb_dredir_left;
		if (nb_redir)
			exec->pipes[i].redir = free_redir(exec->pipes[i].redir);
		i++;
	}
	free(exec->pipes);
	free(exec);
}

void	free_stuff(t_exec *exec, int *childpid)
{
	(void)exec;
	if (childpid)
		free(childpid);
}

void	free_everything(t_exec *exec, int *childpid, t_env *new_env)
{
	free_stuff(exec, childpid);
	free_exec(exec);
	free_env(new_env);
}

