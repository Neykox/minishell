/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:22:45 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 19:43:08 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ctrlc(char *line, int save, int fd)
{
	dup2(save, STDIN_FILENO);
	free(line);
	unlink(".tmp");
	close(save);
	close(fd);
	return (-1);
}

void	check_evar(char **line, t_env *new_env)
{
	int		ret;
	char	*tmp;

	if (*line)
	{
		tmp = check_exp(*line, new_env, &ret);
		free(*line);
		*line = ft_strdup(tmp);
		free(tmp);
	}
}

void	finish_up_heredoc(int fd, int save)
{
	close(fd);
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	close(save);
}

int	heredoc_implementation(t_redir *redir, struct sigaction sa, t_env *new_env)
{
	char	*line;
	int		save;

	save = dup(STDIN_FILENO);
	while (1)
	{
		sa.sa_handler = &ft_signal_heredoc;
		sigaction(SIGINT, &sa, NULL);
		line = readline("> ");
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		if (line == NULL && g_error == 130)
			return (ctrlc(line, save, redir->fd));
		if (line == NULL)
			break ;
		if (!(ft_strncmp(line, redir->redir, ft_strlen(redir->redir))))
			break ;
		check_evar(&line, new_env);
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	finish_up_heredoc(redir->fd, save);
	return (0);
}
