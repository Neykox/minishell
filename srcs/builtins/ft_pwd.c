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
	buf = getcwd(NULL, 0);// si le malloc de getcwd fail, check errno
	if (buf == NULL)
		return (-2);
	ret = write(1, buf, ft_strlen(buf));
	if (ret < 0)
		return (ret);
	write(1, "\n", 1);
	free(buf);
	return (ret);
}
