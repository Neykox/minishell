/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:10:28 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/31 17:04:30 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_echo_flag(char **cmds, int *n, int i, int j)
{
	while (cmds[1] && cmds[j])
	{
		if (cmds[j][0] == '-' && cmds[j][1] == 'n')
			i = 2;
		else
			break ;
		while (cmds[j][i] && cmds[j][i] == 'n')
			i++;
		if (cmds[j][i] != '\0')
		{
			if (j > 1)
				*n = 1;
			else
				*n = 0;
			return (j);
		}
		j++;
	}
	if (cmds[1] && (j > 1 || (cmds[j][i] == '\0' && i > 0)))
		*n = 1;
	else
		*n = 0;
	return (j);
}

char	*ft_strjoin_utils_echo(char *line, char *buf)
{
	char	*line2;

	line2 = ft_strdup(buf);
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

char	*ft_strjoin_echo(char *s1, char *s2, int i)
{
	char	*ret;
	int		c;
	int		size;

	c = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
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
	free(s1);
	return (ret);
}

int	ft_echo(char **cmds, int i, int n, char *ret)
{
	i = check_echo_flag(cmds, &n, 0, 1);
	while (cmds[1] && cmds[i])
	{
		ret = ft_strjoin_utils_echo(ret, cmds[i]);
		if (ret == NULL)
			return (g_error = 1);
		i++;
		if (cmds[i])
		{
			ret = ft_strjoin_utils_echo(ret, " ");
			if (ret == NULL)
				return (g_error = 1);
		}
	}
	if (n == 0 || !(cmds[1]))
		ret = ft_strjoin_utils_echo(ret, "\n");
	else
		ret = ft_strjoin_utils_echo(ret, "");
	if (ret == NULL)
		return (g_error = 1);
	i = write(1, ret, ft_strlen(ret));
	free(ret);
	if (i < 0)
		return (g_error = 1);
	return (g_error = 0);
}
