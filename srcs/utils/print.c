/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:48:00 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/18 17:21:22 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_lxr(t_lxr *lxr)
{
	t_lxr	*tmp;
	tmp = lxr;
	while (1)
	{
		if (tmp)
			printf("Token : %d | Value : %s\n", tmp->token, tmp->value);
		if (tmp)
			tmp = tmp->next;
		if (!(tmp))
			break ;
	}	
}

void	print_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->pipe_content)
		return ;
	else
	{
		while (exec->pipe_content[i])
		{
			write(1, exec->pipe_content[i], ft_strlen(exec->pipe_content[i]));
			write(1, "\n", 1);
			i++;
		}
	}
}
