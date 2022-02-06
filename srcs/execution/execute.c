/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:30:13 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 20:36:13 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_for_child(t_exec *exec, t_env *new_env)
{
	int	i;

	i = 0;
	while (i <= exec->nb_pipe && exec->flag == 0 && exec->save == 0)
	{
		waitpid(exec->childpid[i], &(exec->status), 0);
		if (WIFEXITED(exec->status))
		{
			g_error = WEXITSTATUS(exec->status);
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-1);
		}
		else if (WIFSIGNALED(exec->status))
		{
			g_error = WTERMSIG(exec->status) + 128;
			if (g_error == 131)
				write(1, "Quit (core dumped)\n", 20);
			else if (g_error == 130)
				write(1, "\n", 1);
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	pipe_things_up_3(t_exec *exec, t_env *new_env)
{
	int	i;

	i = 0;
	close_pipes(exec);
	if (wait_for_child(exec, new_env) == -1)
		return (-1);
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].redir != NULL)
			close_redir_fd(exec->pipes[i].redir);
		i++;
	}
	free_stuff(exec, exec->childpid);
	return (0);
}

int	pipe_things_up_2(t_exec *ex, char **envp, t_env *nenv, struct sigaction sa)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= ex->nb_pipe && ex->flag == 0 && ex->save == 0)
	{
		ex->childpid[i] = fork();
		if (ex->childpid[i] == -1)
			return (-2);
		else if (ex->childpid[i] == 0)
		{
			sa.sa_handler = SIG_DFL;
			sigaction(SIGINT, &sa, NULL);
			sigaction(SIGQUIT, &sa, NULL);
			handle_pipe(ex, nenv, j);
			handle_redir(ex, nenv, i);
			child_work(ex, nenv, envp, i);
		}
		i++;
		j++;
	}
	if (pipe_things_up_3(ex, nenv) == -1)
		return (-1);
	return (0);
}

int	pipe_things_up(t_exec *ex, char **envp, t_env *nenv, struct sigaction sa)
{
	int	i;

	i = 0;
	ex->childpid = malloc(sizeof(int) * (ex->nb_pipe + 1));
	if (!(ex->childpid))
		return (-1);
	if (ex->nb_pipe == 0 && ex->pipes[i].nb_cmds)
		check_builtin(ex, ex->pipes[i].cmds[0], nenv);
	if (open_pipe(ex, nenv) < 0)
		return (-1);
	if (pipe_things_up_2(ex, envp, nenv, sa) == -1)
		return (-1);
	return (0);
}

int	execute(t_exec *exec, char **envp, t_env *new_env, struct sigaction sa)
{
	int		i;

	i = 0;
	if (exec->nb_pipe)
	{
		exec->pipefd = init_pipefd(exec->pipefd, exec->nb_pipe);
		if (!exec->pipefd)
			return (1);
	}
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].redir != NULL)
		{
			exec->pipes[i].redir = open_redir_fd(exec->pipes[i].redir,
					sa, new_env);
			if (exec->pipes[i].redir == NULL)
				return (2);
		}
		i++;
	}
	pipe_things_up(exec, envp, new_env, sa);
	free_pipefd(exec->pipefd, exec->nb_pipe);
	return (0);
}
