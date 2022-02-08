/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expender_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:58:06 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/07 15:58:08 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_copy_till_exp(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while ((line[i] && line[i] != '$') || ((line[i] == '$'
				&& (line[i + 1] == '\0' || line[i + 1] == ' '))))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while ((line[i] && line[i] != '$') || ((line[i] == '$'
				&& (line[i + 1] == '\0' || line[i + 1] == ' '))))
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
			*ret = -2;
			return (0);
		}
	}
	return (1);
}

char	*ft_strjoin_utils_exp(char *line, char *buf)
{
	char	*line2;

	line2 = ft_strdup(buf);
	if (line2 == NULL)
		return (NULL);
	if (line == NULL)
		return (line2);
	line = ft_strjoin_echo(line, line2, 0);
	free (line2);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*check_exp_2(char *tmp, int *ret, t_env *env, char *value)
{
	char	*exp;
	// int		i;
	// int temp;

	// i = 0;
	// temp = 0;
	exp = ft_expander(env, value);
	if (free_exp(ret, tmp, exp, 1) == 0)
		return (NULL);
	if (exp[0] == ' ')
	{
		tmp = ft_strjoin_utils_echo(tmp, " ");
		if (tmp == NULL)
		{
			free(exp);
			return (NULL);
		}
		// if (value[i] == '?' && (value[i + 1] == '\0'
		// 			|| value[i + 1] == ' ' || value[i + 1] == '$'))
		// 	i++;
		// while (ft_isalnum_underscore(value[i]) == 1)
		// 	i++;
	}
	// while (exp[temp])
	// 	temp++;
	// if ((temp > 0 && exp[temp - 1] == ' ') || (exp[0] == '\0' && value[i] == ' '))
	tmp = ft_strjoin_utils_echo(tmp, exp);
	if (free_exp(ret, tmp, exp, 2) == 0)
		return (NULL);
	return (tmp);
}

char	*check_exp_3(char *tmp, int *ret, char *value, int *i)
{
	char	*exp;

	exp = ft_copy_till_exp(&value[*i]);
	if (free_exp(ret, tmp, exp, 1) == 0)
		return (NULL);
	tmp = ft_strjoin_utils_echo(tmp, exp);
	if (free_exp(ret, tmp, exp, 2) == 0)
		return (NULL);
	while ((value[*i] && value[*i] != '$') || ((value[*i] == '$'
				&& (value[*i + 1] == '\0' || value[*i + 1] == ' '))))
		*i = *i + 1;
	return (tmp);
}

char	*check_exp(char *value, t_env *envp, int *ret, int i)
{
	char	*tmp;

	tmp = NULL;
	while (value[i])
	{
		if (value[i] == '$' && (value[i + 1] != '\0' && value[i + 1] != ' '))
		{
			tmp = check_exp_2(tmp, ret, envp, &value[i + 1]);
			i++;
			if (value[i] == '?' && (value[i + 1] == '\0'
					|| value[i + 1] == ' ' || value[i + 1] == '$'))
				i++;
			while (ft_isalnum_underscore(value[i]) == 1)
				i++;
		}
		else
			tmp = check_exp_3(tmp, ret, value, &i);
		if (tmp == NULL)
			return (NULL);
	}
	if (i == 0)
		tmp = ft_strdup(value);
	if (free_exp(ret, tmp, NULL, 2) == 0)
		return (NULL);
	return (tmp);
}
