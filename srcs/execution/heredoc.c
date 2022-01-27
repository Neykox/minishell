/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:22:45 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/27 18:24:48 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_implementation(t_redir *redir)
{
	char	*line;
	int		tmp_fd;
	int		ret;

	ret = 0;
	tmp_fd = open(".tmp_heredoc", O_RDWR | O_CREAT, 0644);
	if (tmp_fd < 0)
		return (ret);
	while (1)
	{
		line = readline("> ");
		if (!(ft_strncmp(line, redir->redir, ft_strlen(redir->redir))))
			break ;
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(".tmp_heredoc", O_RDONLY);
	unlink(".tmp_heredoc");
	ret = dup2(tmp_fd, 0);
	if (ret < 0)
		return (ret);
	close(tmp_fd);
	return (ret);
}
