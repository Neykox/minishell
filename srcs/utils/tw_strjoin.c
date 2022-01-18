/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tw_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:31:33 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/18 16:31:54 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tw_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		len_total;
	char	*result;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_total = len_s1 + len_s2 + 1;
	if (!(result = malloc(sizeof(char) * len_total)))
		return (0);
	ft_memmove(result, s1, len_s1);
	ft_memmove(result + len_s1, s2, len_s2);
	result[len_total - 1] = '\0';
	free(s1);
	return (result);
}

