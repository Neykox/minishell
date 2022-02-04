/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:22:45 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/04 17:22:32 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_implementation(t_redir *redir, struct sigaction sa)
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
		if (/*line == NULL && */g_error == 130)
		{
			dup2(save, STDIN_FILENO);
			// break ;
			free(line);
			unlink(".tmp_heredoc");
			close(save);
			close(redir->fd);
			return -1;
		}

		if (line == NULL)
			break ;
		}
		if (!(ft_strncmp(line, redir->redir, ft_strlen(redir->redir))))
			break ;
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	close(redir->fd);
	redir->fd = open(".tmp_heredoc", O_RDONLY);
	unlink(".tmp_heredoc");
	close(save);
	return (0);
}
