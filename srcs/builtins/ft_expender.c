/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:01:37 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/21 16:32:36 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_copy_till_exp(char *line)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = NULL;
	while ((line[i] && line[i] != '$') || ((line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while ((line[i] && line[i] != '$') || ((line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))))
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*check_exp(t_lxr *lxr, t_env *envp, int *ret)
{
	int		i;
	char *tmp = NULL;
	char	*exp;

	i = 0;
	exp = NULL;
	while (lxr->value[i])
	{
		if (lxr->value[i] == '$' && (lxr->value[i + 1] != '\0' && lxr->value[i + 1] != ' '))
		{
			exp = ft_expander(envp, &lxr->value[i + 1]);
			if (exp == NULL)
			{
				if (tmp != NULL)
					free(tmp);
				*ret = -2;
				return (NULL);
			}
			tmp = ft_strjoin_utils(tmp, exp);
			if (tmp == NULL)
			{
				*ret =-2;
				return (NULL);
			}
			i++;
			if (lxr->value[i] == '?' && (lxr->value[i + 1] == '\0' || lxr->value[i + 1] == ' ' || lxr->value[i + 1] == '$'))
				i++;
			while (ft_isalnum_underscore(lxr->value[i]) == 1)
				i++;
		}
		else
		{
			exp = ft_copy_till_exp(&lxr->value[i]);
			if (exp == NULL)
			{
				if (tmp != NULL)
					free(tmp);
				*ret = -2;
				return (NULL);
			}
			tmp = ft_strjoin_utils(tmp, exp);
			if (tmp == NULL)
			{
				*ret = -2;
				return (NULL);
			}
			while ((lxr->value[i] && lxr->value[i] != '$') || ((lxr->value[i] == '$' && (lxr->value[i + 1] == '\0' || lxr->value[i + 1] == ' '))))
				i++;
		}
	}
	if (i == 0)
	{
		tmp = ft_strdup(lxr->value);
		if (tmp == NULL)
		{
			*ret = -2;
			return (NULL);
		}
	}
	return (tmp);
}

int    ft_get_expand(t_lxr *lxr, t_env *envp)
{
    char    *tmp;
    int		ret;

    tmp = NULL;
    ret = 0;
	while (lxr)
	{
		if (lxr->token == 0 || lxr->token == 5)
		{
			tmp = check_exp(lxr, envp, &ret);
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
		// NEED MESSAGE D'ERREUR
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

char	*ft_expander(t_env *envp, char *target)//remove $ before sending target
{
	char	*tmp;
	int	i;

	while (envp)
	{
		i = 0;
		while (envp->line[i] && envp->line[i] != '=')
			i++;
		if (ft_strlen_target(target) - i == 0)
		{
			i++;
			if (ft_strncmp(target, envp->line, ft_strlen_target(target)) == 0)
			{
				return (ft_strdup(&envp->line[i]));
				// return (envp->line);//target has been found
			}
		}
		envp = envp->next;
	}
	tmp = malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}
