/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:13:58 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/17 14:14:08 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


#include "../../includes/minishell.h"

// int	destroy_env(char **envp, int size_env, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size_env)
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// 	if (line != NULL)
// 		free(line);
// 	return (-2);
// }

// char	**ft_copy_env(char **envp)
// {
// 	int	i;
// 	char	**tmp;

// 	i = 0;
// 	tmp = NULL;
// 	while (envp[i])
// 		i++;
// 	tmp = malloc(sizeof(char *) * (i + 1));
// 	if (tmp == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		tmp[i] = ft_strdup(envp[i]);
// 		if (tmp[i] == NULL)
// 		{
// 			destroy_env(tmp, i, NULL);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	tmp[i] = NULL;
// 	return (tmp);
// }

void	ft_lstclear(t_env **lst)
{
	t_env *tmp;
	t_env *curr;

	curr = *lst;
	while (curr)
	{
		tmp = curr->next;
		free(curr->line);
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env *tmp;

	tmp = *alst;
	if (*alst && alst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}

t_env	*ft_lstnew(char *line)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (tmp == NULL)
		return (NULL);
	tmp->line = ft_strdup(line);
	if (tmp->line == NULL)//changed was : if (line == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp->next = NULL;
	return (tmp);
}

t_env	*ft_copy_env(char **envp)
{
	int	i;
	t_env *new_env;
	t_env *tmp;

	i = 0;
	new_env = ft_lstnew(envp[i]);
	if (new_env == NULL)
		return (NULL);
	i++;
	while (envp[i])
	{
		tmp = ft_lstnew(envp[i]);
		if (tmp == NULL)
		{
			ft_lstclear(&new_env);
			return (NULL);
		}
		ft_lstadd_back(&new_env, tmp);
		i++;
	}
	return (new_env);
}
