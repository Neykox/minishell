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

int	write_invalid_arg_exit(char *cmds)
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

void	ft_exit_free(t_exec *exec, t_env *new_env)
{
	close_fds(exec);
	free_pipefd(exec->pipefd, exec->nb_pipe);
	free_everything(exec, exec->childpid, new_env);
}

int	ft_exit_failled_write(t_exec *exec, t_env *env, char *cpy, char **status)
{
	ft_exit_free(exec, env);
	if (status[1])
		free(cpy);
	g_error = 1;
	return (-3);
}

int	ft_exit_writes(t_exec *exec, t_env *env, char *cpy, char **status)
{
	int	i;

	i = 0;
	while (status[1] && status[1][i])
	{
		if (ft_isnum(status[1][i]) == 0)
		{
			ft_exit_free(exec, env);
			exit(write_invalid_arg_exit(cpy));
		}
		i++;
	}
	if (status[1] && status[2])
	{
		g_error = 1;
		if (write(1, "bash: exit: too many arguments\n", 31) < 0)
			return (ft_exit_failled_write(exec, env, cpy, status));
		free(cpy);
		return (0);
	}
	return (1);
}

int	ft_exit(char **status, t_env *new_env, t_exec *exec, int i)
{
	char	*cpy;
	int		ret_atoi;

	if (status[1])
	{
		cpy = ft_strdup(status[1]);
		if (cpy == NULL)
			return (-2);
		ret_atoi = ft_atoi(status[1]);
	}
	if (exec->nb_pipe == 0)
		if (write(1, "exit\n", 5) < 0)
			return (ft_exit_failled_write(exec, new_env, cpy, status));
	i = ft_exit_writes(exec, new_env, cpy, status);
	if (i == 0 || i == -3)
		return (i);
	if (status[1])
	{
		ft_exit_free(exec, new_env);
		free(cpy);
		exit(ret_atoi);
	}
	ft_exit_free(exec, new_env);
	exit(g_error);
	return (0);
}
