/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 06:29:21 by aleroy            #+#    #+#             */
/*   Updated: 2020/11/18 06:29:23 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		j;
	int		result;
	int		sign;

	j = 0;
	sign = 1;
	result = 0;
	while ((str[j] >= 9 && str[j] <= 13) || str[j] == 32)
		j++;
	if (str[j] == '-')
		sign = -1;
	if (str[j] == '-' || str[j] == '+')
		j++;
	while (str[j] != '\0' && str[j] >= '0' && str[j] <= '9')
	{
		result = (result * 10) + (str[j] - 48);
		j++;
	}
	return (result * sign);
}
