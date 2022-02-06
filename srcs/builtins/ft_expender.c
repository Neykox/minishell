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

char	*ft_copy_till_exp(char *line)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = NULL;
	while ((line[i] && line[i] != '$') || ((line[i] == '$' &&
		(line[i + 1] == '\0' || line[i + 1] == ' '))))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while ((line[i] && line[i] != '$') || ((line[i] == '$' &&
		(line[i + 1] == '\0' || line[i + 1] == ' '))))
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	free_exp(int *ret, char *tmp, char *exp, int i)
{
	if (i == 1)
	{
		if (exp == NULL)
		{
			if (tmp != NULL)
				free(tmp);
			*ret = -2;
			return (0);
		}
	}
	else if (i == 2)
	{
		if (exp)
			free(exp);
		if (tmp == NULL)
		{
			*ret =-2;
			return (0);
		}
	}
	return (1);
}

char	*check_exp(char *value, t_env *envp, int *ret)
{
	int		i;
	char 	*tmp;
	char	*exp;

	i = 0;
	tmp = NULL;
	exp = NULL;
	while (value[i])
	{
		if (value[i] == '$' && (value[i + 1] != '\0' && value[i + 1] != ' '))
		{
			exp = ft_expander(envp, &value[i + 1]);
			if (free_exp(ret, tmp, exp, 1) == 0)
				return (NULL);
			tmp = ft_strjoin_utils_echo(tmp, exp);
			if (free_exp(ret, tmp, exp, 2) == 0)
				return (NULL);
			i++;
			if (value[i] == '?' && (value[i + 1] == '\0' || value[i + 1] == ' ' || value[i + 1] == '$'))
				i++;
			while (ft_isalnum_underscore(value[i]) == 1)
				i++;
		}
		else
		{
			exp = ft_copy_till_exp(&value[i]);
			if (free_exp(ret, tmp, exp, 1) == 0)
				return (NULL);
			tmp = ft_strjoin_utils_echo(tmp, exp);
			if (free_exp(ret, tmp, exp, 2) == 0)
				return (NULL);
			while ((value[i] && value[i] != '$') || ((value[i] == '$' && (value[i + 1] == '\0' || value[i + 1] == ' '))))
				i++;
		}
	}
	if (i == 0)
	{
		tmp = ft_strdup(value);
		if (free_exp(ret, tmp, exp, 2) == 0)
				return (NULL);
	}
	return (tmp);
}

int	ft_get_expand(t_lxr *lxr, t_env *envp, int ret)
{
	char	*tmp;

	tmp = NULL;
	while (lxr)
	{
		if (lxr->token == 0 || lxr->token == 5)
		{
			tmp = check_exp(lxr->value, envp, &ret);
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

char    *remove_spaces(char *str, int i, int s, char *tmp)
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
				return (remove_spaces(ft_strdup(&envp->line[i]), 0, 0, NULL));
		}
		envp = envp->next;
	}
	tmp = malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}
