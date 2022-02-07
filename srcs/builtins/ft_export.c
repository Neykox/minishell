/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:05 by user42            #+#    #+#             */
/*   Updated: 2022/02/06 20:52:43 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	modif_interro(t_env *envp, char *error)
{
	char	*tmp;

	if (error == NULL)
		return (-2);
	tmp = ft_strjoin_utils("?=", error);
	free(error);
	if (tmp == NULL)
		return (-2);
	if (add_line(envp, tmp) == -2)
	{
		free(tmp);
		return (-2);
	}
	free(tmp);
	return (0);
}

int	write_invalid_id_export(char *cmds, int *export_ret)
{
	int	ret;

	*export_ret = 1;
	ret = write(1, "bash: export: `", 15);
	if (ret < 0)
		return (-3);
	ret = write(1, cmds, ft_strlen(cmds));
	if (ret < 0)
		return (-3);
	ret = write(1, "': not a valid identifier\n", 26);
	if (ret < 0)
		return (-3);
	return (-1);
}

int	write_no_arg(t_env *env, int ret, int eg)
{
	while (env)
	{
		if (env->line[0] != '?')
		{
			eg = 0;
			while (env->line[eg] && env->line[eg] != '=')
				eg++;
			eg++;
			ret = write(1, "declare -x ", 11);
			if (ret < 0)
			{
				g_error = 1;
				return (-3);
			}
			ret = write(1, env->line, eg);
			ret = write(1, "\"", 1);
			ret = write(1, &env->line[eg], ft_strlen(&env->line[eg]));
			ret = write(1, "\"\n", 2);
		}
		env = env->next;
	}
	g_error = 0;
	return (0);
}

int	free_export(int error, int i, int ret, t_env *envp)
{
	if (error == -2 || error == -3)
	{
		g_error = 1;
		return (error);
	}
	if (i == 1)
		return (write_no_arg(envp, 0, 0));
	g_error = ret;
	return (0);
}

int	ft_export(char **cmds, t_env *envp, char *line)
{
	int	error;
	int	ret;
	int	i;

	ret = 0;
	i = 1;
	while (cmds[1] && cmds[i])
	{
		error = check_value_export(cmds[i], &line);
		if (error == -2)
			return (free_export(error, i, ret, envp));
		if (ft_isalpha_underscore(cmds[i][0]) == 0 || error == -4)
			error = write_invalid_id_export(cmds[i], &ret);
		if (error == 0)
			error = add_line(envp, line);
		if (error == -2 || error == -3)
			return (free_export(error, i, ret, envp));
		i++;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (free_export(0, i, ret, envp));
}
