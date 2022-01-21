/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:14:20 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/21 12:22:39 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsing_error(char *value, int ret)
{
	if (ret == 1)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, value, ft_strlen(value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	if (ret == 2)
		write(2, "minishell: syntax error: uneven number of quotes\n", 49);
	if (ret == 3)
		write(2, "minishell: failed allocating memory for token values\n", 53);
	if (ret == 4)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, value, ft_strlen(value));
		write(2, "'", 1);
		write(2, "\n", 1);
	}
}

int	syntax_checker(t_lxr *lxr)
{
	t_lxr	*parser;

	if (!lxr)
		return (3);
	parser = lxr;
	if (parser->token == PIPE)
	{
		if (parser->next->token != WSPACE)
			print_parsing_error(parser->next->value, 1);
		else
			print_parsing_error(parser->next->next->value, 1);
		return (1);
	}
	while (1)
	{
		if (!parser)
			return (0);
		if (parser->token == QUOTE_ERROR)
			return (2);
		if (parser->token == WSPACE || parser->token == WORD || parser->token == END
			|| parser->token == SQUOTE || parser->token == DQUOTE)
			parser = parser->next;
		else if (parser->token == REDIR_STDIN || parser->token == REDIR_STDOUT
			|| parser->token == DREDIR_LEFT || parser->token == DREDIR_RIGHT)
		{
			parser = parser->next;
			if (parser->token == WSPACE)
				parser = parser->next;
			if (parser->token == QUOTE_ERROR)
				return (2);
			else if (parser->token != WORD && parser->token != SQUOTE && 
				parser->token != DQUOTE)
			{
				print_parsing_error(parser->value, 1);
				return (1);
			}
		}
		else if (parser->token == PIPE)
		{
			parser = parser->next;
			if (parser->token == WSPACE)
				parser = parser->next;
			if (parser->token == QUOTE_ERROR)
				return (2);
			else if (parser->token == END)
			{
				print_parsing_error(parser->value, 1);
				return (1);
			}
		}
	}
}
/*
t_exec *parse_pipes(t_exec *exec, t_lxr *lxr, int pos)
{
	int		i;
	int		j;
	t_lxr	*pipe_parser;
	t_lxr	*tmp;
	t_lxr	*prev;

	i = 0;
	j = 0;
	tmp = lxr;
	while (1)
	{
		if (j == pos)
			break ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
	pipe_parser = tmp;
	while (1)
	{
		if (tmp->token == END || tmp->token == PIPE)
			return (pipe_parser);
		if (tmp->token != PIPE)
		{
			//prev = tmp;
			tmp = tmp->next;
		}
		else if (tmp->token == PIPE)
		{

		}
	}
	while (1)
	{
		if (!pipe_parser)
			break ;
		if (pipe_parser->token != PIPE && pipe_parser->token != END)
			pipe_parser = pipe_parser->next;
		else if (pipe_parser->token == PIPE || pipe_parser->token == END)
		{
			while (tmp->token != PIPE && tmp->token != END)
			{
				if (!(exec->pipes[i].pipe_content))
					exec->pipes[i].pipe_content = ft_strdup(tmp->value);
				else
					exec->pipes[i].pipe_content = tw_strjoin(exec->pipes[i].pipe_content, tmp->value);
				tmp = tmp->next;
			}
			i++;
			tmp = tmp->next;
			pipe_parser = pipe_parser->next;
		}
	}
	return (exec);
}


int	count_redir(char *content, char redir)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	while (content[i])
	{
		if (content[i] == redir)
			ret++;
		i++;
	}
	return (ret);
}*/

int		count_token(t_lxr *lxr, int token, int pos)
{
	t_lxr	*tmp;
	int		i;
	int		j;

	tmp = lxr;
	i = 0;
	j = 0;
	while (1)
	{
		if (j == pos)
			break ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
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

char	**parse_redir(int nb_redir, t_lxr *lxr, int token, int pos)
{
	int		i;
	int		j;
	char	**ret;
	t_lxr	*tmp;

	i = 0;
	j = 0;
	tmp = lxr;
	ret = malloc(sizeof(char *) * (nb_redir + 1));
	if (!(ret))
		return (NULL);
	while (1)
	{
		if (j == pos)
			break ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token != token)
			tmp = tmp->next;
		else if (tmp->token == token)
		{
			tmp = tmp->next;
			if (tmp->token != WSPACE)
				ret[i] = ft_strdup(tmp->value);
			else
				ret[i] = ft_strdup(tmp->next->value);
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

int		count_commands(t_lxr *lxr, int pos)
{
	int		ret;
	int		j;
	t_lxr	*tmp;

	tmp = lxr;
	ret = 0;
	j = 0;
	while (1)
	{
		if (j == pos)
			break ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT || tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
			//if (tmp->token == WORD || tmp->token == SQUOTE || tmp->token == DQUOTE)
				//tmp = tmp->next;
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
	int		j;
	char	**cmds;
	t_lxr	*tmp;

	i = 0;
	j = 0;
	tmp = lxr;
	cmds = malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	while (1)
	{
		if (j == pos)
			break ;
		if (tmp->token != PIPE)
			tmp = tmp->next;
		else if (tmp->token == PIPE)
		{
			j++;
			tmp = tmp->next;
		}
	}
	while (1)
	{
		if (!tmp || tmp->token == PIPE)
			break ;
		if (tmp->token == REDIR_STDIN || tmp->token == REDIR_STDOUT || tmp->token == DREDIR_RIGHT || tmp->token == DREDIR_LEFT)
		{
			tmp = tmp->next;
			if (tmp->token == WSPACE)
				tmp = tmp->next;
			//if (tmp->token == WORD || tmp->token == SQUOTE || tmp->token == DQUOTE)
				//tmp = tmp->next;
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

int	parse_values(t_lxr *lxr, t_exec *exec)
{
	int	i;

	i = 0;
	exec->nb_pipe = count_token(lxr, PIPE, i);
	exec->pipes = malloc(sizeof(t_pipes) * (exec->nb_pipe + 1));
	if (!(exec->pipes))
		return (3);
	while (i <= exec->nb_pipe)
	{
		exec->pipes[i].nb_redir_stdin = count_token(/*exec->pipes[i].pipe_content*/lxr, /*'<'*/REDIR_STDIN, i);
		if (exec->pipes[i].nb_redir_stdin != 0)
			exec->pipes[i].redir_stdin = parse_redir(exec->pipes[i].nb_redir_stdin, lxr, REDIR_STDIN, i);
		exec->pipes[i].nb_redir_stdout = count_token(/*exec->pipes[i].pipe_content*/lxr, /*'>'*/REDIR_STDOUT, i);
		if (exec->pipes[i].nb_redir_stdout != 0)
			exec->pipes[i].redir_stdout = parse_redir(exec->pipes[i].nb_redir_stdout, lxr, REDIR_STDOUT, i);
		exec->pipes[i].nb_dredir_right = count_token(/*exec->pipes[i].pipe_content*/lxr, /*'<'*/DREDIR_RIGHT, i);
		if (exec->pipes[i].nb_dredir_right != 0)
			exec->pipes[i].dredir_right = parse_redir(exec->pipes[i].nb_redir_stdin, lxr, DREDIR_RIGHT, i);
		exec->pipes[i].nb_dredir_left = count_token(/*exec->pipes[i].pipe_content*/lxr, /*'>'*/DREDIR_LEFT, i);
		if (exec->pipes[i].nb_dredir_left != 0)
			exec->pipes[i].dredir_left = parse_redir(exec->pipes[i].nb_redir_stdout, lxr, DREDIR_LEFT, i);
		exec->pipes[i].nb_cmds = count_commands(lxr, i);
		exec->pipes[i].cmds = parse_commands(exec->pipes[i].nb_cmds, lxr, i);
		i++;
	}
	return (0);
}

int	parser(t_lxr *lxr, t_exec *exec)
{
	int	ret;
	int	ret_parsing;

	ret_parsing = 0;
	ret = syntax_checker(lxr);
	if (ret == 2 || ret == 3)
		print_parsing_error(NULL, ret);
	else if (ret == 0)
		parse_values(lxr, exec);
	if (ret_parsing == 0)
		return (ret);
	else
		return (ret_parsing);
}
