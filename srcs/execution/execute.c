/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:30:13 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/25 14:42:59 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_commands(char **cmds, char **envp)
{
	char	*path;
	char	**cmd_paths;
	int		i;
	char	*finalcmd;
	char	*error;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = envp[i] + 5;
	cmd_paths = tweaked_split(path, ':');
	i = 0;
	while (cmd_paths[i])
	{
		finalcmd = ft_strjoin(cmd_paths[i], cmds[0], 0);
		if (!(access(finalcmd, F_OK)))
			execve(finalcmd, cmds, envp);
		else
			i++;
		free(finalcmd);
	}
	//perror(cmds[0]);
	error = strerror(errno);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int	pipe_things_up(t_exec *exec, int **pipefd, char **envp)
{
	int	i;
	int	j;
	int	childpid;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < exec->nb_pipe)
	{
		if (pipe(pipefd[i]) == -1)
			return (1);
		i++;
	}
	i = 0;
	while (i <= exec->nb_pipe)
	{
		childpid = fork();
		if (childpid == -1)
			return (2);
		else if (childpid == 0)
		{
			if (j < exec->nb_pipe)
			{
				if (dup2(pipefd[j][1], 1) < 0)
					exit (1);
			}
			if (j != 0)
			{
				if (dup2(pipefd[j - 1][0], 0) < 0)
					exit (1);
			}
			while (k < exec->nb_pipe)
			{
				if (k != j)
				{
					close(pipefd[k][0]);
					close(pipefd[k][1]);
				}
				k++;
			}
			k = 0;
			while (k < exec->pipes[i].nb_redir_stdin)
			{
				if (dup2(exec->pipes[i].fd_redir_stdin[k], 0) < 0)
					exit (1);
				k++;
			}
			k = 0;
			while (k < exec->pipes[i].nb_redir_stdout)
			{
				if (dup2(exec->pipes[i].fd_redir_stdout[k], 1) < 0)
					exit (1);
				k++;
			}
			k = 0;
			exec_commands(exec->pipes[i].cmds, envp);
			exit (1);
		}
		i++;
		j++;
	}
	while (k < exec->nb_pipe)
	{
		close(pipefd[k][0]);
		close(pipefd[k][1]);
		k++;
	}
	i = 0;
	while (i <= exec->nb_pipe)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

int	execute(t_exec *exec, char **envp)
{
	int		**pipefd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (exec->nb_pipe)
	{
		pipefd = malloc(sizeof(int *) * (exec->nb_pipe));
		if (!(pipefd))
			return (1);
		while (i < exec->nb_pipe)
		{
			pipefd[i] = malloc(sizeof(int) * 2);
			if (!(pipefd[i]))
				return (1);
			i++;
		}
	}
	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].nb_redir_stdin)
		{
			exec->pipes[i].fd_redir_stdin = malloc(sizeof(int) * (exec->pipes[i].nb_redir_stdin));
			if (!(exec->pipes[i].fd_redir_stdin))
				return (1);
		}
		if (exec->pipes[i].nb_redir_stdout)
		{
			exec->pipes[i].fd_redir_stdout = malloc(sizeof(int) * (exec->pipes[i].nb_redir_stdout));
			if (!(exec->pipes[i].fd_redir_stdout))
				return (1);
		}
		if (exec->pipes[i].nb_dredir_left)
		{
			exec->pipes[i].fd_dredir_left = malloc(sizeof(int) * (exec->pipes[i].nb_dredir_left));
			if (!(exec->pipes[i].fd_dredir_left))
				return (1);
		}
		if (exec->pipes[i].nb_dredir_right)
		{
			exec->pipes[i].fd_dredir_right = malloc(sizeof(int) * (exec->pipes[i].nb_dredir_right));
			if (!(exec->pipes[i].fd_dredir_right))
				return (1);
		}
		i++;
	}
	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].nb_redir_stdin)
		{
			while (j < exec->pipes[i].nb_redir_stdin)
			{
				exec->pipes[i].fd_redir_stdin[j] = open(exec->pipes[i].redir_stdin[j], O_RDONLY);
				if (exec->pipes[i].fd_redir_stdin[j] < 0)
				{
					perror(exec->pipes[i].redir_stdin[j]);
					return (2);
				}
				j++;
			}
			j = 0;
		}
		if (exec->pipes[i].nb_redir_stdout)
		{
			while (j < exec->pipes[i].nb_redir_stdout)
			{
				exec->pipes[i].fd_redir_stdout[j] = open(exec->pipes[i].redir_stdout[j], O_TRUNC | O_RDWR | O_CREAT, 0644);
				if (exec->pipes[i].fd_redir_stdout[j] < 0)
				{
					perror(exec->pipes[i].redir_stdout[j]);
					return (2);
				}
				j++;
			}
			j = 0;
		}
		i++;
	}
	pipe_things_up(exec, pipefd, envp);
	return (0);
}
