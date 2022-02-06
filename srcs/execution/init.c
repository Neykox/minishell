/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:05:54 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 18:20:27 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_redir_fd(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (1)
	{
		if (!tmp)
			break ;
		else if (tmp->fd)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

t_redir	*open_redir_fd(t_redir *redir, struct sigaction sa, t_env *new_env)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_STDIN)
			tmp->fd = open(tmp->redir, O_RDONLY);
		else if (tmp->type == REDIR_STDOUT)
			tmp->fd = open(tmp->redir, O_TRUNC | O_RDWR | O_CREAT, 0644);
		else if (tmp->type == DREDIR_RIGHT)
			tmp->fd = open(tmp->redir, O_APPEND | O_RDWR | O_CREAT, 0644);
		else if (tmp->type == DREDIR_LEFT)
		{
			tmp->fd = open(".tmp", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
			if (heredoc_implementation(tmp, sa, new_env) < 0)
			{
				free_redir(redir);
				return (NULL);
			}
		}
		if (tmp->fd < 0)
			perror(tmp->redir);
		tmp = tmp->next;
	}
	return (redir);
}

int	**init_pipefd(int **pipefd, int nb_pipe)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipefd = malloc(sizeof(int *) * (nb_pipe));
	if (!(pipefd))
		return (0);
	while (i < nb_pipe)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!(pipefd[i]))
		{
			while (j < i)
			{
				free(pipefd[j]);
				j++;
			}
			free(pipefd);
			return (0);
		}
		i++;
	}
	return (pipefd);
}
