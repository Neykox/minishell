/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/08 14:27:15 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_token(t_lxr *lxr, int token, int pos, int i)
{
	t_lxr	*tmp;

	tmp = lxr;
	tmp = move_tmp(tmp, pos);
	while (1)
	{
		if (token == PIPE)
		{
			if (tmp->token == END)
				return (i);
			if (tmp->token == token)
				i++;
			tmp = tmp->next;
		}
		else
		{
			if (tmp->token == END || tmp->token == PIPE)
				return (i);
			if (tmp->token == token)
				i++;
			tmp = tmp->next;
		}
	}
}

t_redir	*build_redir(t_redir *redir, t_lxr *tmp)
{
	t_redir	*redir_cell;

	redir_cell = malloc(sizeof(t_redir));
	if (!redir_cell)
		return (NULL);
	redir_cell->type = tmp->token;
	tmp = tmp->next;
	if (tmp->token != WSPACE)
		redir_cell->redir = ft_strdup(tmp->value);
	else
		redir_cell->redir = ft_strdup(tmp->next->value);
	redir_cell->next = NULL;
	build_redir_ll(&redir, redir_cell);
	return (redir);
}

t_redir	*parse_redir(t_lxr *lxr, int pos, t_redir *redir, t_pipes pipes)
{
	t_lxr	*tmp;

	tmp = lxr;
	tmp = move_tmp(tmp, pos);
	if (pipes.nb_redir_stdin == 0
		&& pipes.nb_redir_stdout == 0
		&& pipes.nb_dredir_right == 0
		&& pipes.nb_dredir_left == 0)
		return (redir);
	while (1)
	{
		if (!tmp || tmp->token == PIPE || tmp->token == END)
			break ;
		else if (tmp->token == WORD || tmp->token == SQUOTE
			|| tmp->token == DQUOTE || tmp->token == WSPACE)
			tmp = tmp->next;
		else if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT
			|| tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			redir = build_redir(redir, tmp);
			tmp = tmp->next;
		}
	}
	return (redir);
}

int	parse_values(t_lxr *lxr, t_exec *exec)
{
	int	i;

	i = -1;
	exec = init_exec(exec);
	exec->nb_pipe = count_token(lxr, PIPE, 0, 0);
	exec->pipes = malloc(sizeof(t_pipes) * (exec->nb_pipe + 1));
	if (!(exec->pipes))
		return (3);
	while (++i <= exec->nb_pipe)
	{
		exec->pipes[i].redir = NULL;
		exec->pipes[i].nb_redir_stdin = count_token(lxr, REDIR_STDIN, i, 0);
		exec->pipes[i].nb_redir_stdout = count_token(lxr, REDIR_STDOUT, i, 0);
		exec->pipes[i].nb_dredir_right = count_token(lxr, DREDIR_RIGHT, i, 0);
		exec->pipes[i].nb_dredir_left = count_token(lxr, DREDIR_LEFT, i, 0);
		exec->pipes[i].redir = parse_redir(lxr, i, exec->pipes[i].redir,
				exec->pipes[i]);
		exec->pipes[i].nb_cmds = count_commands(lxr, i, 0);
		exec->pipes[i].tokens = parse_tokens(exec->pipes[i].nb_cmds, lxr, i);
		if (exec->pipes[i].nb_cmds)
			exec->pipes[i].cmds = parse_commands(exec->pipes[i].nb_cmds,
					lxr, i);
	}
	return (0);
}
