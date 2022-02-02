/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:05 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:41:06 by user42           ###   ########.fr       */
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

int write_invalid_id_export(char *cmds)
{
	int	ret;

	ret = write(1, "bash: export: `", 15);
	if (ret < 0)
		return (-3);
	ret = write(1, cmds, ft_strlen(cmds));
	if (ret < 0)
		return (-3);
	ret = write(1, "': not a valid identifier", 25);
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
		env = env->next;
	}
	return (0);
}

int	ft_export(char **cmds, t_env *envp)
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
			return (error);//malloc issue but arg was correct
		if (error == -1)
			ret = -1;
		if (ft_isalpha_underscore(cmds[i][0]) == 0)
			error = write_invalid_id_export(cmds[i]);
		if (error == 0)
			error = add_line(envp, line);
		if (error == -2 ||error == -3)
			return (error);//malloc issue || -3 == write error
		i++;
	}
	if (i == 1)
		return (write_no_arg(envp));
	return (ret);
}

// bash: export: `[hi=hi': not a valid identifier

//export with no arg give alpabatically sorted env output
//declare -x hi2="hi  hi=hello"
