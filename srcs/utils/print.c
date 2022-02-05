/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:48:00 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/05 17:52:58 by nel-masr         ###   ########.fr       */
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

void	print_redir(t_redir *redir, int pos)
{
	t_redir	*tmp;
	tmp = redir;
	printf("pipes[%d]\n", pos);
	while (1)
	{
		if (tmp)
			printf("Type : %d | Value : %s | fd : %d\n", tmp->type, tmp->redir, tmp->fd);
		if (tmp)
			tmp = tmp->next;
		if (!(tmp))
			break ;
	}	
}

void	print_pipes(t_exec *exec)
{
	int	i;
	int	l;

	i = 0;
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
			printf("nb_redir_stdin : %d | nb_redir_stdout : %d | nb_dredir_right : %d | nb_dredir_left : %d\n", exec->pipes[i].nb_redir_stdin, exec->pipes[i].nb_redir_stdout, exec->pipes[i].nb_dredir_right, exec->pipes[i].nb_dredir_left);
			print_redir(exec->pipes[i].redir, i);
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
