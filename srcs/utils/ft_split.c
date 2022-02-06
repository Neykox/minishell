/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <nel-masr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:40:03 by nel-masr          #+#    #+#             */
/*   Updated: 2022/02/06 20:01:22 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	**free_that_string(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static	int	count_words(char const *s, char c)
{
	int	i;
	int	wdcounter;
	int	flag;

	wdcounter = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			flag = 0;
		else if (flag == 0)
		{
			wdcounter++;
			flag = 1;
		}
		i++;
	}
	return (wdcounter);
}

static	int	count_size(char const *s, char c, int pos)
{
	int	wdsize;

	wdsize = 0;
	while (s[pos] != c && s[pos])
	{
		pos++;
		wdsize++;
	}
	return (wdsize);
}

static	void	split_that_string(char const *s, char c, char **tab, int count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	while (s[i] && ++j < count)
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(sizeof(char) * (count_size(s, c, i) + 1));
		if (!tab[j])
		{
			free_that_string(tab);
			return ;
		}
		while (s[i] != c && s[i])
		{
			tab[j][k] = s[i];
			k++;
			i++;
		}
		tab[j][k] = '\0';
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		wdcounter;

	if (!s)
		return (NULL);
	wdcounter = count_words(s, c);
	tab = malloc(sizeof(char *) * (wdcounter + 1));
	if (!tab)
		return (NULL);
	split_that_string(s, c, tab, wdcounter);
	tab[wdcounter] = 0;
	return (tab);
}
