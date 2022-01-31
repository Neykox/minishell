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

		if (error == 0)
			error = add_line(envp, line);
		if (error == -2)
			return (error);//malloc issue
		if (error == -1)
			ret = -1;

		i++;
	}
	return (ret);
}
