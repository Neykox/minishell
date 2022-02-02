/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:22:45 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/28 16:21:54 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_implementation(t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!(ft_strncmp(line, redir->redir, ft_strlen(redir->redir))))
			break ;
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	close(redir->fd);
	redir->fd = open(".tmp_heredoc", O_RDONLY);
	unlink(".tmp_heredoc");
	return (0);
}
