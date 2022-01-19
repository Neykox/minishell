/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:48:00 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/19 17:09:32 by nel-masr         ###   ########.fr       */
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
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!exec->pipes)
		return ;
	else
	{
		while (i <= exec->nb_pipe)
		{
			printf("pipe_content : %s | nb_redir_stdin : %d | nb_redir_stdout : %d\n", exec->pipes[i].pipe_content, exec->pipes[i].nb_redir_stdin, exec->pipes[i].nb_redir_stdout);
			while (j < exec->pipes[i].nb_redir_stdin)
			{
				printf("pipes[%d]->redir_stdin[%d] : %s\n", i, j, exec->pipes[i].redir_stdin[j]);
				j++;
			}
			j = 0;
			while (k < exec->pipes[i].nb_redir_stdout)
			{
				printf("pipes[%d]->redir_stdout[%d] : %s\n", i, k, exec->pipes[i].redir_stdout[k]);
				k++;
			}
			k = 0;
			//write(1, exec->pipes[i].pipe_content, ft_strlen(exec->pipes[i].pipe_content));
			//write(1, "\n", 1);
			i++;
		}
	}
}
