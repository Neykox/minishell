/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:07:11 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 19:55:38 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*node;

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

void	free_cmds(char **cmds, int nb_cmds)
{
	int	j;

	j = 0;
	while (j < nb_cmds)
	{
		free(cmds[j]);
		j++;
	}
	free(cmds);
}

void	free_exec(t_exec *exec)
{
	int	i;
	int	nb_redir;

	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].nb_cmds)
			free_cmds(exec->pipes[i].cmds, exec->pipes[i].nb_cmds);
		nb_redir = exec->pipes[i].nb_redir_stdin
			+ exec->pipes[i].nb_redir_stdout
			+ exec->pipes[i].nb_dredir_right
			+ exec->pipes[i].nb_dredir_left;
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
