/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:48:00 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/21 12:32:39 by nel-masr         ###   ########.fr       */
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
	int	m;
	int	n;

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
			printf("nb_dredir_right : %d | nb_dredir_left : %d\n", exec->pipes[i].nb_dredir_right, exec->pipes[i].nb_dredir_left);
			while (m < exec->pipes[i].nb_dredir_right)
			{
				//if (exec->pipes[i].redir_stdin[j])
					printf("pipes[%d]->dredir_right[%d] : %s\n", i, m, exec->pipes[i].dredir_right[m]);
				m++;
			}
			m = 0;
			while (n < exec->pipes[i].nb_dredir_left)
			{
				//if (exec->pipes[i].redir_stdout[k])
					printf("pipes[%d]->dredir_left[%d] : %s\n", i, n, exec->pipes[i].dredir_left[n]);
				n++;
			}
			n = 0;
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
