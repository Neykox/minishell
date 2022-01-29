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

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// int check_value_export(t_lxr *lxr, char **line)
// {
// 	int i;
// 	char	*value;

// 	i = 0;
// 	value = NULL;
// 	while (lxr->value[i] && lxr->value[i] != '=' && ft_isalpha_underscore(lxr->value[i]) == 1)
// 		i++;
// 	if (i == 0 || lxr->value[i] != '=')
// 		return (-1);
// 	//should be HELLO= at this point
// 	*line = ft_strdup(lxr->value);
// 	if (line == NULL)
// 		return (-2);
// 	if (ft_isalnum(lxr->value[i + 1])== 1)
// 		lxr = lxr->next;
// 	else
// 	{
// 		if (lxr->next->token == 4 || lxr->next->token == 5)
// 		{
// 			lxr = lxr->next;
// 			value = ft_strdup(lxr->value);
// 			if (value == NULL)
// 			{
// 				free(*line);
// 				return (-2);
// 			}
// 			*line = ft_strjoin_utils(*line, value);
// 			if (*line == NULL)
// 				return (-2);
// 		}
// 	}
// 	return (0);
// }

int check_value_export(char *cmds, char **line)
{
	int i;

	i = 0;
	while (cmds[i] && cmds[i] != '=' && ft_isalpha_underscore(cmds[i]) == 1)
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

// int	ft_export(t_lxr *lxr, t_env *envp)
// {
// 	char	*line;
// 	int	error;
// 	int	ret;

// 	line = NULL;
// 	ret = 0;
// 	while (lxr->token == 0 || lxr->token == 4 || lxr->token == 5 || lxr->token == 9)//word/quote/space
// 	{
// 		if (lxr->token == 0 || lxr->token == 4 || lxr->token == 5)
// 			error = check_value_export(lxr, &line);
// 		if (error == -2)
// 			return (error);//malloc issue but arg was correct
// 		if (error == -1)
// 			ret = -1;

// 		if ((lxr->token == 0 || lxr->token == 4 || lxr->token == 5) && error == 0)
// 			error = add_line(envp, line);
// 		if (error == -2)
// 			return (error);//malloc issue
// 		if (error == -1)
// 			ret = -1;

// 		lxr = lxr->next;
// 	}
// 	return (ret);
// }

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
