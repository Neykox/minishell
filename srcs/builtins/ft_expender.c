/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:01:37 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/03 17:50:34 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_expand(t_lxr *lxr, t_env *envp, int ret)
{
	char	*tmp;

	tmp = NULL;
	while (lxr)
	{
		if (lxr->token == 0 || lxr->token == 5)
		{
			tmp = check_exp(lxr->value, envp, &ret, 0);
			if (ret == -2)
			{
				if (tmp != NULL)
					free(tmp);
				return (-2);
			}
			if (lxr->value[0] == '$' && tmp[0] == '\0')
				lxr->token = -2;
			free(lxr->value);
			lxr->value = ft_strdup(tmp);
			free(tmp);
			if (lxr->value == NULL)
				return (-2);
		}
		lxr = lxr->next;
	}
	return (0);
}

int	ft_strlen_target(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?' && (str[1] == '\0' || str[1] == ' ' || str[1] == '$'))
		return (1);
	if (str[i] && ft_isalpha_underscore(str[i]) == 1)
		i++;
	if (i > 0)
		while (str[i] && ft_isalnum_underscore(str[i]) == 1)
			i++;
	return (i);
}

char	*remove_spaces(char *str, int i, int s, char *tmp)
{
	if (str == NULL)
		return (NULL);
	tmp = ft_strdup(str);
	if (tmp == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[s])
	{
		while (str[s] && str[s] == ' ')
			s++;
		if (str[s] && s > 0 && str[s - 1] == ' ')
			if (i > 0 && tmp[i - 1] != ' ')
				tmp[i++] = ' ';
		while (str[s] && str[s] != ' ')
		{
			tmp[i] = str[s];
			i++;
			s++;
		}
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char	*ft_expander(t_env *envp, char *target)
{
	char	*tmp;
	int		i;

	while (envp)
	{
		i = 0;
		while (envp->line[i] && envp->line[i] != '=')
			i++;
		if (ft_strlen_target(target) - i == 0)
		{
			i++;
			if (ft_strncmp(target, envp->line, ft_strlen_target(target)) == 0)
				// return (remove_spaces(ft_strdup(&envp->line[i]), 0, 0, NULL));
				return (ft_strdup(&envp->line[i]));
		}
		envp = envp->next;
	}
	tmp = malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}
