/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/14 16:01:00 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process(char *line, char **env)
{
	if (!line || line[0] == EOF)
	{
		ft_putstr_fd("\n", 2);
		free(line);
		return (0) ;
	}
	else if (ft_strlen(line) > 1)
	{
		if (!strcmp("pwd\n", line))
			ft_pwd();
		else if (!strcmp("env\n", line))
			ft_env(env);
		else if (!strncmp("echo", line, ft_strlen("echo")))
			ft_echo(line);
		else if (!strncmp("unset", line, ft_strlen("unset")))
			ft_unset(env, line);
		else if (!strcmp("exit\n", line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	t_data	*data;
	
	data = set_data(env);
	printf("%d\n", data->nb);
	while (1)
	{
		ft_putstr_fd("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ", 2);
		line = get_next_line(0);
		ft_parser(line);
		if (!process(line, env))
			break ;
	}
	return (0);
}