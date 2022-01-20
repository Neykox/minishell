/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:48:00 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/20 17:04:09 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_lxr(t_lxr *lxr)
{
	t_lxr	*tmp;
	tmp = lxr;
	printf("****************************************************************\n");
	printf("******************            LEXER          *******************\n");
	printf("****************************************************************\n");
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
	int	l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	printf("****************************************************************\n");
	printf("******************           PARSER          *******************\n");
	printf("****************************************************************\n");
	if (!exec->pipes)
		return ;
	else
	{
		while (i <= exec->nb_pipe)
		{
			printf("nb_redir_stdin : %d | nb_redir_stdout : %d\n", exec->pipes[i].nb_redir_stdin, exec->pipes[i].nb_redir_stdout);
			while (j < exec->pipes[i].nb_redir_stdin)
			{
				//if (exec->pipes[i].redir_stdin[j])
					printf("pipes[%d]->redir_stdin[%d] : %s\n", i, j, exec->pipes[i].redir_stdin[j]);
				j++;
			}
			j = 0;
			while (k < exec->pipes[i].nb_redir_stdout)
			{
				//if (exec->pipes[i].redir_stdout[k])
					printf("pipes[%d]->redir_stdout[%d] : %s\n", i, k, exec->pipes[i].redir_stdout[k]);
				k++;
			}
			k = 0;
			while (l < exec->pipes[i].nb_cmds)
			{
				printf("pipes[%d]->cmds[%d] : |%s|\n", i, l, exec->pipes[i].cmds[l]);
				l++;
			}
			l = 0;
			printf("\n");
			i++;
		}
	}
}
