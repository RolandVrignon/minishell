/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:12:50 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/02 19:42:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
static void	replace_pwd(char *path)
{
	int i;
	char **env;

	i = 0;
	env = get_data()->env;
	while (env[i] && strncmp("PWD", env[i], 3) != 0)
		i++;
	env[i] = ft_strjoin("PWD=\0", path);
	if (!env[i])
		return ;
}

int	ft_cd(char *line)
{
	char	**cd;
	int		i;

	cd = memcenter(MALLOC, 0, ft_split(line, ' '), BUILTIN);
	if (!cd)
		return (0);
	i = -1;
	while (cd[++i])
		memcenter(MALLOC, 0, cd[i], BUILTIN);
	memcenter(MALLOC, 0, cd[i], BUILTIN);
	chdir(cd[1]);
	replace_pwd(cd[1]);
	return (1);
}*/

static void	replace_pwd(char *path, char **env)
{
	int i;

	i = 0;
	while (env[i] && strncmp("PWD", env[i], 3) != 0)
		i++;
	env[i] = ft_strjoin("PWD=\0", path);
	if (!env[i])
		return ;
}

int	ft_cd(t_data **data, char **env)
{
	char	**cd;
	int		i;

	cd = memcenter(MALLOC, 0, ft_split((*data)->line, ' '), BUILTIN); // pas le bon, il faut chopper les elements parse
	if (!cd)
		return (0);
	i = -1;
	while (cd[++i])
		memcenter(MALLOC, 0, cd[i], BUILTIN);
	memcenter(MALLOC, 0, cd[i], BUILTIN);
	chdir(cd[1]);
	replace_pwd(cd[1], env);
	return (1);
}
