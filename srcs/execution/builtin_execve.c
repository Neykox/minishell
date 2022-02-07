/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:22:23 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/07 15:54:03 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_dot_slash(t_exec *exec, char **envp, char **cmds, t_env *new_env)
{
	if (cmds[0][0] == '/' || cmds[0][0] == '.')
	{
		if (!(access(cmds[0], F_OK & X_OK)))
		{
			if (execve(cmds[0], cmds, envp) < 0)
				perror(cmds[0]);
			free_everything(exec, exec->childpid, new_env);
			exit (126);
		}
		else
		{
			perror(cmds[0]);
			return (-1);
		}
	}
	return (0);
}

void	search_and_execute(t_env *tmp, char **envp, char **cmds)
{
	char	**cmd_paths;
	char	*finalcmd;
	int		i;

	i = 0;
	cmd_paths = tweaked_split(tmp->line + 5, ':');
	while (cmd_paths[i])
	{
		finalcmd = ft_strjoin(cmd_paths[i], cmds[0], 0);
		if (!(access(finalcmd, F_OK & X_OK)))
		{
			if (execve(finalcmd, cmds, envp) < 0)
			{
				free(finalcmd);
				break ;
			}
		}
		else
			i++;
		free(finalcmd);
	}
	t_free_that_string(cmd_paths);
}

void	exec_commands(char **cmds, char **envp, t_env *new_env, t_exec *exec)
{
	t_env	*tmp;

	if (handle_dot_slash(exec, envp, cmds, new_env) < 0)
		return ;
	else
	{
		tmp = new_env;
		while (tmp != NULL && ft_strncmp(tmp->line, "PATH=", 5))
			tmp = tmp->next;
		if (tmp == NULL)
		{
			if (execve(cmds[0], cmds, envp) < 0)
			{
				perror(cmds[0]);
				return ;
			}
		}
		else
			search_and_execute(tmp, envp, cmds);
	}
	perror(cmds[0]);
}

int	builtin_checker(t_exec *exec, t_env *new_env, int ret, int i)
{
	if (exec->pipes[i].nb_cmds == 0)
		return (1);
	if (!(ft_strncmp(exec->pipes[i].cmds[0], "echo", 5)))
		ret = ft_echo(exec->pipes[i].cmds, 0, 0, NULL);
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "unset", 6)))
		ret = ft_unset(exec->pipes[i].cmds, new_env, NULL);
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "cd", 3)))
		ret = ft_cd(exec->pipes[i].cmds, exec->pipes[i].nb_cmds, new_env);
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "pwd", 4)))
		ret = ft_pwd();
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "export", 7)))
		ret = ft_export(exec->pipes[i].cmds, new_env, NULL);
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "env", 4)))
		ret = ft_env(new_env);
	else if (!(ft_strncmp(exec->pipes[i].cmds[0], "exit", 5)))
		ret = ft_exit(exec->pipes[i].cmds[1], new_env, exec);
	else
		ret = -10;
	if (ret == -3 || ret == -2 || ret == 1)
		perror(exec->pipes[i].cmds[0]);
	if (modif_interro(new_env, ft_itoa(g_error)) == -2)
		return (-2);
	return (ret);
}

void	check_builtin(t_exec *exec, char *cmd, t_env *new_env)
{
	int	i;

	i = 0;
	if (!(ft_strncmp(cmd, "cd", 3)) || !(ft_strncmp(cmd, "unset", 7))
		|| !(ft_strncmp(cmd, "exit", 5)))
	{
		builtin_checker(exec, new_env, 0, i);
		exec->flag = 1;
	}
	if (!(ft_strncmp(cmd, "export", 7)) && exec->pipes[i].cmds[1])
	{
		builtin_checker(exec, new_env, 0, i);
		exec->flag = 1;
	}
}
