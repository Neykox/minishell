/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:43 by user42            #+#    #+#             */
/*   Updated: 2022/02/07 12:21:49 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int write_invalid_arg_exit(char *cmds)
{
	int	ret;

	ret = write(1, "bash: exit: ", 12);
	if (ret < 0)
	{
		free(cmds);
		return (-3);
	}
	ret = write(1, cmds, ft_strlen(cmds));
	if (ret < 0)
	{
		free(cmds);
		return (-3);
	}
	free(cmds);
	ret = write(1, ": numeric argument required\n", 28);
	if (ret < 0)
		return (-3);
	return (2);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_exit(char *status, t_env *new_env, /*int nb_pipe*/t_exec *exec)
{
	int		ret;
	int		i;
	char	*cpy;
	int		ret_atoi;

	(void)new_env;
	if (status)
	{
		cpy = ft_strdup(status);
		ret_atoi = ft_atoi(status);
	}
	i = 0;
	ret = 0;
	if (exec->nb_pipe == 0)
		ret = write(1, "exit\n", 5);
	if (ret < 0)
	{
		close_fds(exec);
		free_pipefd(exec->pipefd, exec->nb_pipe);
		free_everything(exec, exec->childpid, new_env);
		if (status)
			free(cpy);
		g_error = 1;
		return (-3);
	}
	
	while (status && status[i])
	{
		if (ft_isnum(status[i]) == 0)
		{
			close_fds(exec);
			free_pipefd(exec->pipefd, exec->nb_pipe);
			free_everything(exec, exec->childpid, new_env);
			exit(write_invalid_arg_exit(cpy/*status*/));
		}
		i++;
	}


	if (status)
	{
		close_fds(exec);
		free_pipefd(exec->pipefd, exec->nb_pipe);
		free_everything(exec, exec->childpid, new_env);
		free(cpy);
		exit(ret_atoi/*ft_atoi(status)*/);
	}
	close_fds(exec);
	free_pipefd(exec->pipefd, exec->nb_pipe);
	free_everything(exec, exec->childpid, new_env);
	exit(g_error);
	return (0);
}
 
