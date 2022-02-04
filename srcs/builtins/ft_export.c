/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:05 by user42            #+#    #+#             */
/*   Updated: 2022/02/03 19:16:21 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	ft_isalnum_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int check_value_export(char *cmds, char **line)
{
	int i;

	i = 0;
	if (cmds[i] && cmds[i] != '=' && ft_isalpha_underscore(cmds[i]) == 1)
		i++;
	if (i > 0)
		while (cmds[i] && cmds[i] != '=' && ft_isalnum_underscore(cmds[i]) == 1)
			i++;
	if (i == 0 || cmds[i] != '=')
		return (-1);
	//should be HELLO= at this point
	*line = ft_strdup(cmds);
	if (line == NULL)
		return (-2);
	return (0);
}

int	not_in_env(t_env *envp, char *line)
{
	t_env *tmp;

	tmp = ft_lstnew(line);
	if  (tmp == NULL)
	{
		free(line);
		// ft_lstclear(&envp);
		return (-2);
	}
	ft_lstadd_back(&envp, tmp);
	return (0);
}

int	add_line(t_env *envp, char *line)
{
	t_env *tmp;
	int	eg;

	eg = 0;
	tmp = envp;
	while (line[eg] != '=')
		eg++;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, line, eg) == 0)
		{
			free(tmp->line);
			tmp->line = ft_strdup(line);
			if (tmp->line == NULL)
			{
				// destroy_env(tmp);
				return (-2);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	return (not_in_env(envp, line));
}

int modif_interro(t_env *envp, char *error)
{
	char	*tmp;

	if (error == NULL)
		return (-2);
	tmp = ft_strjoin_utils("?=", error);
	free(error);
	if (tmp == NULL)
		return (-2);
	//printf("tmp = %s\n", tmp);
	if (add_line(envp, tmp) == -2)
	{
		free(tmp);
		return (-2);
	}
	free(tmp);
	return (0);
}

int write_invalid_id_export(char *cmds, int *export_ret)
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

int	write_no_arg(t_env *env)
{
	int ret;
	int eg;

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
				return (-3);
			ret = write(1, env->line, eg);
			if (ret < 0)
				return (-3);
			ret = write(1, "\"", 1);
			if (ret < 0)
				return (-3);
			ret = write(1, &env->line[eg], ft_strlen(&env->line[eg]));
			if (ret < 0)
				return (-3);
			ret = write(1, "\"\n", 2);
			if (ret < 0)
				return (-3);
		}
		env = env->next;
	}
	return (0);
}

int	ft_export(char **cmds, t_env *envp)//need to free(line) not sure were tho
{
	char	*line;
	int	error;
	int	ret;
	int	i;

	line = NULL;
	ret = 0;
	i = 1;
	while (cmds[i])
	{
		error = check_value_export(cmds[i], &line);
		if (error == -2)
		{
			g_error = 1;
			return (error);
		}
		if (ft_isalpha_underscore(cmds[i][0]) == 0)
			error = write_invalid_id_export(cmds[i], &ret);
		if (error == 0)
			error = add_line(envp, line);
		if (error == -2 ||error == -3)
		{
			g_error = 1;
			return (error);//malloc issue || -3 == write error
		}
		i++;
	}
	if (i == 1)
		return (g_error = write_no_arg(envp));
	g_error = ret;
	return (0);
}

// bash: export: `[hi=hi': not a valid identifier

//export with no arg give alpabatically sorted env output
//declare -x hi2="hi  hi=hello"
