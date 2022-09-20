/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/20 15:52:58 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process(char *line, char **env)
{
	if (line == NULL || !strcmp("exit", line))
	{
		ft_putstr_fd("\n", 2);
		return (0) ;
	}
	else if (ft_strlen(line) > 1)
	{
		if (!strcmp("pwd", line))
			ft_pwd();
		else if (!strcmp("env", line))
			ft_env(env);
		else if (!strncmp("echo", line, ft_strlen("echo")))
			ft_echo(line);
		else if (!strncmp("unset", line, ft_strlen("unset")))
			ft_unset(env, line);
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line = NULL;
	t_data	*data;
	
	data = set_data(env);
	while (1)
	{
		line = readline("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		data->lexer = ft_lexer(line);
		while (data->lexer)
		{
			printf("TYPE : %d | CONTENU : %s\n", data->lexer->type, data->lexer->content);
			data->lexer = data->lexer->next;
		}
		if (!process(line, env))
			break ;
		memcenter(FREE_WHERE, 0, NULL, LEXER);
	}
	memcenter(PURGE, 0, NULL, NOTHING);
	return (0);
}
