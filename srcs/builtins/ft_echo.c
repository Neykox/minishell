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

// int check_echo_flag(char **cmds, int *n)
// {
// 	int i;
// 	int	j;

// 	j = 1;
// 	while (cmds[j] && cmds[j][0] == '-' && cmds[j][1] == 'n')
// 	{
// 		i = 2;
// 		while (cmds[j][i] && cmds[j][i] == 'n')
// 			i++;
// 		if (cmds[j][i] != '\0')
// 		{
// 			if (j > 1)
// 				*n = 1;
// 			return (j);
// 		}
// 		j++;
// 	}
// 	if (cmds[1] && j == 1 && cmds[j][i] == '\0')
// 		*n = 1;
// 	else
// 		*n = 0;
// 	return (1);
// }

int check_echo_flag(char **cmds, int *n)
{
	int i;
	int	j;

	j = 1;
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
	if (cmds[1] && (j > 1 || cmds[j][i] == '\0'))
		*n = 1;
	else
		*n = 0;
	return (j);
}

// int	ft_echo(t_pipes *pipes)
// {
// 	int	n;
// 	int	i;
// 	char	*ret;

// 	ret = NULL;
// 	if (pipes->cmds[1])
// 		i = check_echo_flag(pipes->cmds[1], &n);
// 	while (pipes->cmds[1] && pipes->cmds[i])
// 	{
// 		ret = ft_strjoin_utils(ret, pipes->cmds[i]);
// 		if (ret == NULL)
// 			return (-2);
// 		i++;
// 		if (pipes->cmds[i])
// 		{
// 			ret = ft_strjoin_utils(ret, " ");
// 			if (ret == NULL)
// 				return (-2);
// 		}
// 	}
// 	if (n == 0 || !(pipes->cmds[1]))
// 		ret = ft_strjoin_utils(ret, "\n");
// 	else
// 		ret = ft_strjoin_utils(ret, "");
// 	if (ret == NULL)
// 		return (-2);
// 	write(1, ret, ft_strlen(ret));
// 	free(ret);
// 	return (0);
// }

char	*ft_strjoin_utils_echo(char *line, char *buf)
{
	char	*line2;

	// if (buf == NULL)//new if
	// 	return (NULL);
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

int	ft_echo(char **cmds)//should return -2 not set ret2 to -2, ret2 is reset before exit too
{
	int	n;
	int	i;
	char	*ret;
	int	ret2;

	ret = NULL;
	i = check_echo_flag(cmds, &n);
	while (cmds[1] && cmds[i])
	{
		ret = ft_strjoin_utils_echo(ret, cmds[i]);
		if (ret == NULL)
		{
			ret2 = -2;
			return (g_error = 1);
		}
		i++;
		if (cmds[i])
		{
			ret = ft_strjoin_utils_echo(ret, " ");
			if (ret == NULL)
			{
				ret2 = -2;
				return (g_error = 1);
			}
		}
	}
	if (n == 0 || !(cmds[1]))
		ret = ft_strjoin_utils_echo(ret, "\n");
	else
		ret = ft_strjoin_utils_echo(ret, "");
	if (ret == NULL)
	{
		ret2 = -2;
		return (g_error = 1);
	}
	ret2 = write(1, ret, ft_strlen(ret));
	free(ret);
	if (ret2 < 0)
		return (g_error = 1);
	return (g_error = 0);
}
