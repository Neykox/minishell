/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:40:45 by user42            #+#    #+#             */
/*   Updated: 2022/01/31 17:22:31 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// chdir(path_name);
// On success, zero is returned.  On error, -1 is returned, and
//        errno is set to indicate the error.

char	*remove_eg(char *str)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if ( str[i] == '=')
		i++;
	tmp = ft_strdup(&str[i]);
	return (tmp);
}

char	*find_in_env(t_env *envp, char *line, int *ret)
{
	t_env *tmp;
	char	*str;
	int	eg;

	eg = 0;
	str = NULL;
	tmp = envp;
	while (line[eg])
		eg++;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, line, eg) == 0)
		{
			str = remove_eg(tmp->line);
			if (str == NULL)
				*ret = -2;
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int modif_oldpwd(t_env *env)
{
	char *line;
	char *oldpwd[3];
	int ret;

	ret = 0;
	oldpwd[0] = NULL;
	line = find_in_env(env, "PWD=", &ret);
	if (ret == -2)
		return (-2);
	if (line == NULL)
		oldpwd[1] = ft_strjoin_utils("OLDPWD=", "");
	else
		oldpwd[1] = ft_strjoin_utils("OLDPWD=", line);
	if (oldpwd[1] == NULL)
		return (-2);
	oldpwd[2] = NULL;
	ret = ft_export(oldpwd, env);
	free(line);
	free(oldpwd[1]);
	if (ret == -2)
		return (-2);
	return (0);
}

int modif_pwd(t_env *env)
{
	char *line;
	char *pwd[3];
	int ret;

	line = NULL;
	ret = 0;
	pwd[0] = NULL;
	line = getcwd(NULL, 0);// si le malloc de getcwd fail, check errno
	if (line == NULL)
		return (-2);
	pwd[1] = ft_strjoin_utils("PWD=", line);
	free(line);
	if (pwd[1] == NULL)
		return (-2);
	pwd[2] = NULL;
	ret = ft_export(pwd, env);
	free(pwd[1]);
	if (ret == -2)
		return (-2);
	return (0);
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
	// (void)env;
	ret = modif_oldpwd(env);
	if (ret == -2)
		return (-2);
	ret = modif_pwd(env);
	if (ret == -2)
		return (-3);
	return (0);
}
