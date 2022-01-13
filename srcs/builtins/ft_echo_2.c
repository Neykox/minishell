/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:36:50 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/13 15:59:22 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_utils_echo(char *line, char *buf)
{
	char	*line2;

	line2 = ft_strdup_echo(buf);
	if (line2 == NULL)
		return (NULL);
	if (line == NULL)
		return (line2);
	line = ft_strjoin_echo(line, line2, 0);
	free (line2);
	if (line == NULL)
		return (NULL);
	return (line);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_echo(const char *s1)
{
	char	*copie;
	char	*str;
	int		i;

	i = 0;
	str = (char *) s1;
	copie = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	if (copie == NULL)
		return (NULL);
	while (str[i])
	{
		copie[i] = str[i];
		i++;
	}
	copie[i] = '\n';
	i++;
	copie[i] = '\0';
	return (copie);
}

char	*ft_strjoin_echo(char const *s1, char const *s2, int i)
{
	char	*ret;
	int		c;
	int		size;

	c = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2;
	ret = malloc(sizeof(char) * size);
	if (ret == NULL)
		return (NULL);
	while (s1[c])
	{
		ret[i] = s1[c];
		i++;
		c++;
	}
	c = 0;
	while (s2[c])
	{
		ret[i] = s2[c];
		i++;
		c++;
	}
	ret[i] = '\0';
	return (ret);
}

