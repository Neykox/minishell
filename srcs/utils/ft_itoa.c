/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:23:04 by aleroy            #+#    #+#             */
/*   Updated: 2020/11/24 14:23:06 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_size_itoa(int n)
{
	int i;

	i = 1;
	if (n == -2147483648)
	{
		n++;
		n = -n;
		i++;
	}
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_reverse(char *tab)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	if (tab[i] == '-')
		i++;
	while (tab[n])
		n++;
	n--;
	while (i < n)
	{
		c = tab[i];
		tab[i] = tab[n];
		tab[n] = c;
		i++;
		n--;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	m;
	char		*tab;

	i = 0;
	m = n;
	if (!(tab = malloc(sizeof(char) * (ft_size_itoa(n) + 1))))
		return (NULL);
	if (m < 0)
	{
		tab[i++] = '-';
		m = -m;
	}
	if (m == 0)
		tab[i++] = '0';
	while (m > 0)
	{
		tab[i++] = m % 10 + 48;
		m = m / 10;
	}
	tab[i] = '\0';
	tab = ft_reverse(tab);
	return (tab);
}
