/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:33:25 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 21:06:14 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_redir(t_redir *redir)
{
	t_redir	*tmp;
	int		ret;

	tmp = redir;
	ret = 0;
	while (1)
	{
		if (!tmp)
			break ;
		else if (tmp->type == REDIR_STDIN || tmp->type == DREDIR_LEFT)
		{
			ret = dup2(tmp->fd, 0);
			close(tmp->fd);
		}
		else if (tmp->type == REDIR_STDOUT || tmp->type == DREDIR_RIGHT)
		{
			ret = dup2(tmp->fd, 1);
			close(tmp->fd);
		}
		if (ret < 0)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}

int	open_pipe(t_exec *exec, t_env *new_env)
{
	int	i;

	i = 0;
	while (i < exec->nb_pipe)
	{
		if (pipe(exec->pipefd[i]) == -1)
		{
			printf("pipe a foire: %d\n", errno);
			g_error = 1;
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-1);
			exec->save = i;
			break ;
		}
		i++;
	}
	return (0);
}

void	handle_pipe(t_exec *exec, t_env *new_env, int j)
{
	int	k;

	k = 0;
	if (j < exec->nb_pipe)
	{
		if (dup2(exec->pipefd[j][1], 1) < 0)
		{
			free_everything(exec, exec->childpid, new_env);
			exit (1);
		}
	}
	if (j != 0)
	{
		if (dup2(exec->pipefd[j - 1][0], 0) < 0)
		{
			free_everything(exec, exec->childpid, new_env);
			exit (1);
		}
	}
	while (k < exec->nb_pipe)
	{
		close(exec->pipefd[k][0]);
		close(exec->pipefd[k][1]);
		k++;
	}
}

void	handle_redir(t_exec *exec, t_env *new_env, int i)
{
	int	ret;

	ret = 0;
	if (exec->pipes[i].redir != NULL)
	{
		ret = exec_redir(exec->pipes[i].redir);
		if (ret < 0)
		{
			free_everything(exec, exec->childpid, new_env);
			exit (1);
		}
	}
}

void	child_work(t_exec *exec, t_env *new_env, char **envp, int i)
{
	int	ret;

	ret = 0;
	ret = builtin_checker(exec, new_env, 0, i);
	if (ret == -10 && exec->pipes[i].nb_cmds)
	{
		exec = check_cmds(exec);
		exec_commands(exec->pipes[i].cmds, envp, new_env, exec);
		close_fds(exec);
		free_pipefd(exec->pipefd, exec->nb_pipe);
		free_everything(exec, exec->childpid, new_env);
		if (errno == EAGAIN)
			exit(126);
		exit (127);
	}
	else
	{
		close_fds(exec);
		free_pipefd(exec->pipefd, exec->nb_pipe);
		free_everything(exec, exec->childpid, new_env);
		exit(g_error);
	}
}
