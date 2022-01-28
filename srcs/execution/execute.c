/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:30:13 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/28 17:25:45 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_commands(char **cmds, char **envp)
{
	char	*path;
	char	**cmd_paths;
	int		i;
	char	*finalcmd;

	i = 0;
	if (cmds[0][0] == '/' || cmds[0][0] == '.')
	{
		if (!(access(cmds[0], X_OK)))
			execve(cmds[0], cmds, envp);
	}
	else
	{
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
			i++;
		path = envp[i] + 5;
		cmd_paths = tweaked_split(path, ':');
		i = 0;
		while (cmd_paths[i])
		{
			finalcmd = ft_strjoin(cmd_paths[i], cmds[0], 0);
			if (!(access(finalcmd, F_OK & X_OK)))
				execve(finalcmd, cmds, envp);
			else
				i++;
			free(finalcmd);
		}
	}
	perror(cmds[0]);
}

int	exec_redir(t_redir *redir)
{
	t_redir *tmp;
	int		ret;

	tmp = redir;
	ret = 0;
	while (1)
	{
		if (!tmp)
			break ;
		else if (tmp->type == REDIR_STDIN)
		{
			ret = dup2(tmp->fd, 0);
			if (ret < 0)
				return (ret);
			close(tmp->fd);
		}
		else if (tmp->type == REDIR_STDOUT || tmp->type == DREDIR_RIGHT)
		{
			ret = dup2(tmp->fd, 1);
			if (ret < 0)
				return (ret);
			close(tmp->fd);
		}
		else if (tmp->type == DREDIR_LEFT)
		{
			ret = dup2(tmp->fd, 0);
			if (ret < 0)
				return (ret);
			close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	builtin_checker(char **cmds)
{
	int ret;

	ret = 1;
	if (!(ft_strncmp(cmds[0], "echo", 4)))
		//send to echo fct
	else if (!(ft_strncmp(cmds[0], "unset", 6)))
		//send to unset fct
	else if (!(ft_strncmp(cmds[0], "cd", 2)))
		//send to cd fct
	else if (!(ft_strncmp(cmds[0], "pwd", 3)))
		//send to pwd fct
	else if (!(ft_strncmp(cmds[0], "export", 6)))
		//send to export fct
	else if (!(ft_strncmp(cmds[0], "env", 3)))
		//send to enc fct
	else if (!(ft_strncmp(cmds[0], "exit", 4)))
		//send to exit fct
	else
		ret = 0;
	return (ret);
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
			if (exec->pipes[i].redir != NULL)
			{
				k = exec_redir(exec->pipes[i].redir);
				if (k < 0)
					exit (1);
			}
			if (!(builtin_checker(exec->pipes[i].cmds)))
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
	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].redir != NULL)
			close_redir_fd(exec->pipes[i].redir);
		i++;
	}
	return (0);
}

void	close_redir_fd(t_redir *redir)
{
	t_redir *tmp;

	tmp = redir;
	while (1)
	{
		if (!tmp)
			break ;
		else if (tmp->fd)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

t_redir	*open_redir_fd(t_redir *redir)
{
	t_redir *tmp;

	tmp = redir;
	while (1)
	{
		if (!tmp)
			break ;
		else if (tmp->type == REDIR_STDIN)
		{
			tmp->fd = open(tmp->redir, O_RDONLY);
			if (tmp->fd < 0)
			{
				perror(tmp->redir);
				return (NULL);
			}
		}
		else if (tmp->type == REDIR_STDOUT)
		{
			tmp->fd = open(tmp->redir, O_TRUNC | O_RDWR | O_CREAT, 0644);
			if (tmp->fd < 0)
			{
				perror(tmp->redir);
				return (NULL);
			}
		}
		else if (tmp->type == DREDIR_RIGHT)
		{
			tmp->fd = open(tmp->redir, O_APPEND | O_RDWR | O_CREAT, 0644);
			if (tmp->fd < 0)
			{
				perror(tmp->redir);
				return (NULL);
			}
		}
		else if (tmp->type == DREDIR_LEFT)
		{
			tmp->fd = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
			if (tmp->fd < 0)
			{
				perror(tmp->redir);
				return (NULL);
			}
			if (heredoc_implementation(tmp) < 0)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (redir);
}

int	execute(t_exec *exec, char **envp)
{
	int		**pipefd;
	int		i;

	i = 0;
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
		if (exec->pipes[i].redir != NULL)
		{
			exec->pipes[i].redir = open_redir_fd(exec->pipes[i].redir);
			if (exec->pipes[i].redir == NULL)
				return (2);
		}
		i++;
	}
	print_pipes(exec);
	pipe_things_up(exec, pipefd, envp);
	return (0);
}
