/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:40:45 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 15:40:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// chdir(path_name);
// On success, zero is returned.  On error, -1 is returned, and
//        errno is set to indicate the error.

// int	ft_cd(t_pipes *pipes, t_env *env)
// {
// 	(void)env;
// 	int	ret;

// 	ret = 0;
// 	if (pipes->nb_cmds > 2)
// 		return (-1);
// 	ret = chdir(pipes->cmds[1]);
// 	if (ret == -1)
// 	{
// 		perror("ft_cd");
// 		return (-1);
// 	}
// 	//change env
// 	return (ret);
// }

char	*find_in_env(t_env *envp, char *line, int *ret)
{
	t_env *tmp;
	char *line2;
	int	eg;

	eg = 0;
	tmp = envp;
	while (line[eg] != '=')
		eg++;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, line, eg) == 0)
		{
			line2 = ft_strdup(tmp->line);
			if (ret == NULL)
				*ret = -2;
			return (line2);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int modif_oldpwd(t_env *env)
{
	char *line;
	char *oldpwd[2];
	int ret;

	ret = 0;
	line = find_in_env(env, "PWD", &ret);
	if (ret == -2)
		return (-2);
	if (line == NULL)
		oldpwd[0] = ft_strjoin_utils("OLDPWD=", "");
	else
		oldpwd[0] = ft_strjoin_utils("OLDPWD=", line);
	if (line == NULL)
		return (-2);
	oldpwd[1] = NULL;
	ret = ft_export(oldpwd, env);
	free(line);
	free(oldpwd[0]);
	if (ret == -2)
		return (-2);
	return (0);
}

int modif_pwd(t_env *env)
{
	char *line;
	char *pwd[2];
	int ret;

	line = NULL;
	ret = 0;
	line = getcwd(line, 0);// si le malloc de getcwd fail, check errno
	if (line == NULL)
		return (-2);
	pwd[0] = ft_strjoin_utils("PWD=", line);
	free(line);
	if (pwd[0] == NULL)
		return (-2);
	pwd[1] = NULL;
	ret = ft_export(pwd, env);
	free(pwd[0]);
	if (ret == -2)
		return (-2);
}

int	ft_cd(char **cmds, int nb_cmds, t_env *env)
{
	int		ret;

	ret = 0;
	if (nb_cmds > 2)
		return (-1);
	ret = chdir(cmds[1]);//check if cmds[1] exist
	if (ret == -1)
	{
		perror("ft_cd");
		return (-1);
	}
	ret = modif_oldpwd(env);
	if (ret == -2)
		return (-2);
	ret = modif_pwd(env);
	if (ret == -2)
		return (-2);
	return (0);
}

// char *line;

// line = find_in_env(env, "PWD");
// if (line == NULL)
// 	OLDPWD[0] = ft_strjoin_utils("OLDPWD=", "");
// else
// 	OLDPWD[0] = ft_strjoin_utils("OLDPWD=", line);
// OLDPWD[1] = NULL;
// ret = ft_export(OLDPWD, env);

// cd;

// char *pwd[2];
// pwd[0] = ft_strjoin_utils("PWD=", getcwd());
// pwd[1] = NULL;
// ret = ft_export(pwd, env);
