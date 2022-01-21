/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:01:37 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/20 12:03:59 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_expander(char **envp, char *target)//remove $ before sending target
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strlen(target) - ft_strlen(envp[i]) == 0)
// 		{
// 			if (ft_strncmp(target, envp[i], ft_strlen(target)) == 0)
// 				return (envp[i]);//target has been found
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*ft_copy_till_exp(char *line)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = NULL;
	while (line[i] && line[i] != '$')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '$')
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}


char	*check_exp(t_lxr *lxr, t_env *envp)
{
	int		i;
	char	*tmp;
	char	*exp;

	i = 0;
	tmp = NULL;
	exp = NULL;
	while (lxr->value[i])
	{
		if (lxr->value[i] == '$')
		{
			exp = ft_expander(envp, &lxr->value[i + 1]);
			if (exp == NULL)
			{
				if (tmp != NULL)
					free(tmp);
				return (NULL);
			}
			tmp = ft_strjoin_utils(tmp, exp);
			if (tmp == NULL)
				return (NULL);
			i++;
			while (ft_isalpha_underscore(lxr->value[i]) == 1)
				i++;
		}
		else
		{
			exp = ft_copy_till_exp(lxr->value);
			if (exp == NULL)
			{
				if (tmp != NULL)
					free(tmp);
				return (NULL);
			}
			tmp = ft_strjoin_utils(tmp, exp);
			if (tmp == NULL)
				return (NULL);
			while (lxr->value[i] && lxr->value[i] != '$')
				i++;
		}
	}
	return (tmp);
}

int	ft_get_expand(t_lxr *lxr, t_env *envp)
{
	char	*tmp;

	// while (lxr->token == 0 || lxr->token == 4 || lxr->token == 5)//modif 0 to value that isnt a keyword/num
	// {
		if (lxr->token == 4)
			return (0);
		else
			tmp = check_exp(lxr, envp);
		if (tmp == NULL)
			return (-2);
		free(lxr->value);
		lxr->value = ft_strdup(tmp);
		free(tmp);
		if (lxr->value == NULL)
			return (-2);
		// lxr = lxr->next;
	// }
	return (0);
}

int	ft_strlen_target(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha_underscore(str[i]) == 1)
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
