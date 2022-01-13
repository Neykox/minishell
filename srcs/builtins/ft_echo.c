/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:10:28 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/13 14:10:30 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_echo_flag(char *ag)
{
	if (ag[0] == '-' && ag[1] == 'n' && ag[2] == '\0')
		return (1);
	return (0);
}

char	*copy_till_token(char *line, char **envp, char token)
{}

char	*ft_echo_exp(t_lxr *lxr, char **envp, int token)
{
	int	i;
	int	e;
	char	*tmp;

	i = 0;
	e = 0;
	while (lxr->value[i])
	{
		if (token == 0)
			copy_till_token(lxr->value, envp, '\0');
		else if (token == 4)
			copy_till_token(lxr->value, envp, '\'');
		else if (token == 5)
			copy_till_token(lxr->value, envp, '"');
		while (lxr->value[i] && lxr->value[i])

		else if (lxr->value[i] == '$' && q == 0)
			add_exp();
	}
}

int	ft_echo(t_lxr *lxr, char **envp)
{
	int	n;
	char	*ret;

	n = check_echo_flag(lxr->value);
	if (n == 1)
		lxr = lxr->next;

	while (lxr->token == 0 || lxr->token == 4 || lxr->token == 5)//modif 0 to value that isnt a keyword/num
	{
		ret = ft_echo_exp(lxr, envp, lxr->token);
		//add space when changing to next : add space between arg
		if (ret == NULL)
			return (-1);
		lxr = lxr->next;
	}

	if (n == 1)
	{
		buf[0] = '\n';
		buf[1] = '\0';
		ret = ft_strjoin_utils(ret, buf);
		if (ret == NULL)
			return (-1);
	}
	write(1, &ret, ft_strlen(ret));
	free(ret);
	return (0);
}
