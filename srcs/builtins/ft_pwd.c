/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:40:56 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:40:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);// si le malloc de getcwd fail, check errno
	if (buf == NULL)
		return ;
	write(1, buf, ft_strlen(buf));
	// write(1, "\n", 1);
	free(buf);
}
