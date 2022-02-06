/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:40:56 by user42            #+#    #+#             */
/*   Updated: 2022/01/31 17:21:54 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*buf;
	int		ret;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		g_error = 1;
		return (-2);
	}
	ret = write(1, buf, ft_strlen(buf));
	if (ret < 0)
	{
		g_error = 1;
		return (1);
	}
	write(1, "\n", 1);
	free(buf);
	return (g_error = 0);
}
