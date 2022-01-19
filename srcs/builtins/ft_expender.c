/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:01:37 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/17 14:01:39 by aleroy           ###   ########.fr       */
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

char	*ft_expander(t_env *envp, char *target)//remove $ before sending target
{
	char	*tmp;
	int	i;

	i = 0;
	while (target && target[i] != '=')
		i++;
	while (envp)
	{
		if (ft_strlen(target) - i == 0)
		{
			if (ft_strncmp(target, envp->line, ft_strlen(target)) == 0)
				return (envp->line);//target has been found
		}
		envp = envp->next;
	}
	tmp = malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}
