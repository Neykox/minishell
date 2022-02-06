/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:19:16 by aleroy            #+#    #+#             */
/*   Updated: 2022/02/06 20:19:17 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_value_unset(char *cmds, char **line)
{
	int	i;

	i = 0;
	if (cmds[i] && ft_isalpha_underscore(cmds[i]) == 1)
		i++;
	if (i > 0)
		while (cmds[i] && ft_isalnum_underscore(cmds[i]) == 1)
			i++;
	if (i == 0 || (ft_isalpha_underscore(cmds[i]) == 0 && cmds[i] != '\0'))
		return (-1);
	*line = ft_strdup(cmds);
	if (*line == NULL)
		return (-2);
	return (0);
}
