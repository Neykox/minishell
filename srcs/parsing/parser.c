/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/27 14:41:53 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr	*move_tmp(t_lxr *tmp, int pos)
{
	int	j;

	j = 0;
	while (1)
	{
		if (j == pos)
			return (tmp) ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
}

int		count_token(t_lxr *lxr, int token, int pos, int i)
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

t_redir	*parse_redir(t_lxr *lxr, int pos, t_redir *redir)
{
	t_lxr	*tmp;

	tmp = lxr;
	tmp = move_tmp(tmp, pos);
	while (1)
	{
		if (!tmp || tmp->token == PIPE || tmp->token == END)
			break ;
		else if (tmp->token == WORD || tmp->token == SQUOTE || tmp->token == DQUOTE
			|| tmp->token == WSPACE)
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

int		count_commands(t_lxr *lxr, int pos)
{
	int		ret;
	t_lxr	*tmp;

	tmp = lxr;
	ret = 0;
	tmp = move_tmp(tmp, pos);
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT || tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
		}
		else if ((tmp->token == WORD || tmp->token == SQUOTE || tmp->token == DQUOTE) && tmp->value)
		{
			ret++;
			while (tmp->next->token == WORD || tmp->next->token == SQUOTE || tmp->next->token == DQUOTE)
			{
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

char	**parse_commands(int nb_cmds, t_lxr *lxr, int pos)
{
	int		i;
	char	**cmds;
	t_lxr	*tmp;

	i = 0;
	tmp = lxr;
	cmds = malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	tmp = move_tmp(tmp, pos);
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT || tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
		}
		else if ((tmp->token == WORD || tmp->token == SQUOTE || tmp->token == DQUOTE) && tmp->value)
		{
			cmds[i] = ft_strdup(tmp->value);
			while (tmp->next->token == WORD || tmp->next->token == SQUOTE || tmp->next->token == DQUOTE)
			{
				tmp = tmp->next;
				cmds[i] = ft_strjoin(cmds[i], tmp->value, 0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	cmds[i] = '\0';
	return (cmds);
}

t_exec	*check_cmds(t_exec *exec)
{
	int		i;
	char	*tmp;
	char	*pwd;
	char	*pwd_slash;

	i = 0;
	pwd = NULL;
	while (i <= exec->nb_pipe)
	{
		if (!(ft_strncmp(exec->pipes[i].cmds[0], "./", 2)))
		{
			tmp = tweaked_strdup(exec->pipes[i].cmds[0]);
			pwd = getcwd(pwd, 0);
			pwd_slash = ft_add_char(pwd, '/');
			free(exec->pipes[i].cmds[0]);
			exec->pipes[i].cmds[0] = ft_strjoin(pwd_slash, tmp, 0);
			free(tmp);
			free(pwd_slash);
		}
		i++;
	}
	return (exec);
}

int	parse_values(t_lxr *lxr, t_exec *exec)
{
	int	i;

	i = -1;
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
		printf("nb_redir_stdin : %d | nb_redir_stdout : %d | nb_dredir_right : %d | nb_dredir_left : %d\n", exec->pipes[i].nb_redir_stdin, exec->pipes[i].nb_redir_stdout, exec->pipes[i].nb_dredir_right, exec->pipes[i].nb_dredir_left);
		if (exec->pipes[i].nb_redir_stdin != 0 || exec->pipes[i].nb_redir_stdout != 0 
			|| exec->pipes[i].nb_dredir_right != 0 || exec->pipes[i].nb_dredir_left != 0)
			exec->pipes[i].redir = parse_redir(lxr, i, exec->pipes[i].redir);
		exec->pipes[i].nb_cmds = count_commands(lxr, i);
		exec->pipes[i].cmds = parse_commands(exec->pipes[i].nb_cmds, lxr, i);
	}
	exec = check_cmds(exec);
	return (0);
}

int	parser(t_lxr *lxr, t_exec *exec)
{
	int	ret;
	int	ret_parsing;

	ret_parsing = 0;
	ret = 0;
	ret = syntax_checker(lxr, ret);
	if (ret == 2 || ret == 3)
		print_parsing_error(NULL, ret);
	else if (ret == 0)
		parse_values(lxr, exec);
	if (ret_parsing == 0)
		return (ret);
	else
		return (ret_parsing);
}
