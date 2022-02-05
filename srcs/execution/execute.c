/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:30:13 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/05 12:25:04 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_commands(char **cmds, char **envp, t_env *new_env)
{
	char	**cmd_paths;
	int		i;
	char	*finalcmd;
	t_env	*tmp;

	i = 0;
	if (cmds[0][0] == '/' || cmds[0][0] == '.')
	{
		if (!(access(cmds[0], F_OK & X_OK)))
		{
			//printf("coucou\n");
			if (execve(cmds[0], cmds, envp) < 0)
				printf("errno = %d\n", errno);
		}
		else
		{
			perror(cmds[0]);
			//printf("hey\nerrno = %d\n", errno);
			return ;
			//if (errno == EAGAIN)
			//	exit(126);
			//else
			//	exit(127);
		}
	}
	else
	{
		tmp =  new_env;
		while (tmp != NULL && ft_strncmp(tmp->line, "PATH=", 5))
			tmp = tmp->next;
		/*
		 * Si PATH unset
		 */
		if (tmp == NULL)
		{
			if (execve(cmds[0], cmds, envp) < 0)
			{
				perror(cmds[0]);
				return ;
				//if (errno == EAGAIN)
				//	exit(126);
				//else
				//	exit(127);
			}	
		}
		/*
		 * Si PATH est trouve
		 */
		else
		{
			cmd_paths = tweaked_split(tmp->line + 5, ':');
			while (cmd_paths[i])
			{
				finalcmd = ft_strjoin(cmd_paths[i], cmds[0], 0);
				if (!(access(finalcmd, F_OK & X_OK)))
				{
					//printf("woohoo\n");
					if (execve(finalcmd, cmds, envp) < 0)
					/*{
						if (errno == EAGAIN)
							exit(126);
						else
							exit(127);
					}*/
						break ;
				}
				else
					i++;
				free(finalcmd);
			}
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
			{
				printf("hgg\n");
				return (ret);
			}
			close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	builtin_checker(char **cmds, int nb_cmds, t_env *new_env, int nb_pipe)
{
	int ret;

	ret = 0;

	//return 1;

	if (nb_cmds == 0)
		return (1);
	if (!(ft_strncmp(cmds[0], "echo", 4)))
	{
		ret = ft_echo(cmds);
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "unset", 5)))
	{
		ret = ft_unset(cmds, new_env);
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "cd", 2)))
	{
		ret = ft_cd(cmds, nb_cmds, new_env);
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "pwd", 3)))
	{
		ret = ft_pwd();
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "export", 6)))
	{
		ret = ft_export(cmds, new_env);
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "env", 3)))
	{
		ret = ft_env(new_env);
		//printf("hello from builtin\n");
	}
	else if (!(ft_strncmp(cmds[0], "exit", 4)))
	{
		ret = ft_exit(cmds[1], new_env, nb_pipe);
		//printf("hello from builtin\n");
	}
	else
		ret = -10;
	if (ret == -3 || ret == -2 || ret == 1)
		perror(cmds[0]);
	// if (g_error != 125 || ret != 0)
	// 	g_error = ret;
	if (modif_interro(new_env, ft_itoa(g_error)) == -2)
		return (-2);
	return (ret);
}

int	pipe_things_up(t_exec *exec, int **pipefd, char **envp, t_env *new_env)
{
	int	i;
	int	j;
	int	*childpid;
	int	k;
	int	status;
	int	flag;
	int ret;

	i = 0;
	j = 0;
	k = 0;
	ret = 0;
	status = 0;
	flag = 0;
	childpid = malloc(sizeof(int) * (exec->nb_pipe + 1));
	if (!(childpid))
		return (-1);
	if (exec->nb_pipe == 0 && exec->pipes[i].nb_cmds)
	{
		if (!(ft_strncmp(exec->pipes[i].cmds[0], "cd", 2)) || !(ft_strncmp(exec->pipes[i].cmds[0], "unset", 6)) || !(ft_strncmp(exec->pipes[i].cmds[0], "exit", 4)))
		{
			builtin_checker(exec->pipes[i].cmds, exec->pipes[i].nb_cmds, new_env, exec->nb_pipe);
			flag = 1;
		}
		if (!(ft_strncmp(exec->pipes[i].cmds[0], "export", 6)) && exec->pipes[i].cmds[1])
		{
			builtin_checker(exec->pipes[i].cmds, exec->pipes[i].nb_cmds, new_env, exec->nb_pipe);
			flag = 1;
		}
	}
	while (i < exec->nb_pipe)
	{
		if (pipe(pipefd[i]) == -1)
			return (1);
		i++;
	}
	i = 0;
	while (i <= exec->nb_pipe && flag == 0)
	{
		childpid[i] = fork();
		if (childpid[i] == -1)
			return (2);
		else if (childpid[i] == 0)
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
				close(pipefd[k][0]);
				close(pipefd[k][1]);
				k++;
			}
			k = 0;
			if (exec->pipes[i].redir != NULL)
			{
				k = exec_redir(exec->pipes[i].redir);
				if (k < 0)
					exit (1);
			}
			ret = builtin_checker(exec->pipes[i].cmds, exec->pipes[i].nb_cmds, new_env, exec->nb_pipe);
			if (ret == -10 && exec->pipes[i].nb_cmds)
			{
				exec = check_cmds(exec);
				exec_commands(exec->pipes[i].cmds, envp, new_env);
				free_everything(exec, childpid, new_env);
				if (errno == EAGAIN)
					exit(126);
				exit (127);
			}
			else
			{
				//free_stuff(exec, childpid);
				//free_exec(exec);
				//free_env(new_env);
				free_everything(exec, childpid, new_env);
				exit(g_error);
			}
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
	while (i <= exec->nb_pipe && flag == 0)
	{
		waitpid(childpid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_error = WEXITSTATUS(status);
			if (modif_interro(new_env, ft_itoa(g_error)) == -2)
				return (-1);
		}
		i++;
	}
	i = 0;
	while (i <= exec->nb_pipe)
	{
		if (exec->pipes[i].redir != NULL)
			close_redir_fd(exec->pipes[i].redir);
		i++;
	}
	//free_stuff(exec, childpid);
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

t_redir	*open_redir_fd(t_redir *redir, struct sigaction sa, t_env *new_env)
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
				perror(tmp->redir);
		}
		else if (tmp->type == REDIR_STDOUT)
		{
			tmp->fd = open(tmp->redir, O_TRUNC | O_RDWR | O_CREAT, 0644);
			if (tmp->fd < 0)
				perror(tmp->redir);
		}
		else if (tmp->type == DREDIR_RIGHT)
		{
			tmp->fd = open(tmp->redir, O_APPEND | O_RDWR | O_CREAT, 0644);
			if (tmp->fd < 0)
				perror(tmp->redir);
		}
		else if (tmp->type == DREDIR_LEFT)
		{
			tmp->fd = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
			if (tmp->fd < 0)
			{
				printf("hello\n");
				perror(tmp->redir);
			}
			if (heredoc_implementation(tmp, sa, new_env) < 0)
			{
				free_redir(redir);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (redir);
}

int	execute(t_exec *exec, char **envp, t_env *new_env, struct sigaction sa)
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
			exec->pipes[i].redir = open_redir_fd(exec->pipes[i].redir, sa, new_env);
			if (exec->pipes[i].redir == NULL)
				return (2);
		}
		i++;
	}
	//print_pipes(exec);
	pipe_things_up(exec, pipefd, envp, new_env);
	return (0);
}
