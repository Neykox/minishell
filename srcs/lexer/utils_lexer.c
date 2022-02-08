/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:44:54 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/08 14:27:06 by nel-masr         ###   ########.fr       */
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

int	malloc_quote(char *line, int j, int k, char quote)
{
	j++;
	while (line[j] != quote && line[j])
	{
		k++;
		j++;
	}
	if (k == -1)
		k = 0;
	return (k);
}

t_exec	*init_exec(t_exec *exec)
{
	exec->save = 0;
	exec->flag = 0;
	exec->status = 0;
	return (exec);
}
