/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:07:11 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/04 20:18:12 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*free_env(t_env *env)
{
	t_env *tmp;
	t_env *node;

	printf("on rentre dans free_env\n");
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
	printf("on a fini de free env\n");
	return (env);
}

t_lxr	*free_lxr(t_lxr *lxr)
{
	t_lxr *tmp;
	t_lxr *node;

	printf("on rentre dans free_lxr\n");
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
	printf("on a fini de free lxr\n");
	return (lxr);
}

t_redir	*free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir *node;

	printf("on rentre dans free_redir\n");
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
	printf("on a fini de free redir");
	return (redir);
}

void	free_exec(t_exec *exec)
{
	int	i;
	int	j;
	int	nb_redir;

	printf("on rentre dans free_exec\n");
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
	free(exec->pipes);
	free(exec);
	printf("on a fini de free exec\n");
}

void	free_stuff(t_exec *exec, int *childpid)
{
	//int	i;
	
	//i = 0;
	(void)exec;
	printf("on rentre dans free_childpid\n");
	if (childpid)
		free(childpid);
	printf("on a fini de free childpid\n");
}
