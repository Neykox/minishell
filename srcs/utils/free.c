/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:07:11 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/05 15:56:19 by nel-masr         ###   ########.fr       */
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
		printf("on est en train de free redir oue oue\n");
		tmp = node;
		node = node->next;
		if (redir->redir)
			free(redir->redir);
		free(tmp);
	}
	redir = NULL;
	printf("on a fini de free redir\n");
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
				printf("on est en train de free les commandes oueoue\n");
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
	printf("on a fini de free exec\n");
}

void	free_stuff(t_exec *exec, int *childpid)
{
	(void)exec;
	printf("on rentre dans free_childpid\n");
	if (childpid)
		free(childpid);
	printf("on a fini de free childpid\n");
}

void	free_everything(t_exec *exec, int *childpid, t_env *new_env)
{
	free_stuff(exec, childpid);
	free_exec(exec);
	free_env(new_env);
}

