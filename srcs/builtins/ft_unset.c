/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:19 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:41:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int check_value(t_lxr *lxr, char *line)
{
	int i;

	i = 0;
	while (lxr->value[i] && ft_isalpha(lxr->value[i]) == 1)
		i++;
	if (i == 0 || (ft_isalpha(lxr->value[i]) == 0 && lxr->value[i] != '\0'))
		return (-1);
	//should be HELLO at this point
	line = ft_strdup(lxr->value);
	if (line == NULL)
		return (-2);
	return (0);
}

int	crush_line(char **envp, char **tmp, int addr)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (i == addr)
		{
			free(envp[i]);
			i++;
		}
		tmp[i] = ft_strdup(tmp[i]);
		if (tmp[i] == NULL)
			return (-2);
		free(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	free(tmp);
	return (0);
}

int	find_line(char **envp, char *line)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * i);
	if (tmp == NULL)
		return (-2);
	tmp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], line, ft_strlen(line)) == 0)
			return (crush_line(envp, tmp, i));
		i++;
	}
	free(tmp);
	return (-1);
}

int	ft_unset(t_lxr *lxr, char **envp)
{
	char	*line;
	int	error;
	int	ret;

	line = NULL;
	ret = 0;
	while (lxr->token == 0 || lxr->token == 4 || lxr->token == 5 || lxr->token == 9)//word/quote/space
	{
		if (lxr->token == 0 || lxr->token == 4 || lxr->token == 5)
			error = check_value(lxr, line);
		if (error == -2)
			return (error);//malloc issue but arg was correct
		if (error == -1)
			ret = -1;

		if (lxr->token == 0 || lxr->token == 4 || lxr->token == 5 && error == 0)
			error = find_line(envp, line);
		if (error == -2)
			return (error);//malloc issue
		if (error == -1)
			ret = -1;

		lxr = lxr->next;
	}
	return (ret);
}
