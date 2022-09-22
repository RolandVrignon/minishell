/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/22 19:19:00 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		builtin(t_data **data)
{
	if ((*data)->line == NULL || !strcmp("exit", (*data)->line))
		return (-1);
	else if (ft_strlen((*data)->line) > 1)
	{
		if (!strcmp("pwd", (*data)->line))
			return (ft_pwd());
		else if (!strcmp("env", (*data)->line))
			return (ft_env((*data)->env));
		else if (!strncmp("cd", (*data)->line, ft_strlen("cd")))
			return (ft_cd((*data)->line));
		else if (!strncmp("echo", (*data)->line, ft_strlen("echo")))
			return (ft_echo((*data)->line));
		else if (!strncmp("unset", (*data)->line, ft_strlen("unset")))
			return (ft_unset((*data)->env, (*data)->line));
		else if (!strncmp("export", (*data)->line, ft_strlen("export"))) // EXPORT TEST
			return (ft_export(data));
	}
	return (6);	
}

int		process(t_data **data)
{
	int			return_value;
	t_parse		*parsing;
	
	parsing = NULL;
	return_value = builtin(data);
	if (return_value != 6)
		return (return_value);
	// parsing = simulate_parse(parsing);
	(void)parsing;
	return (1);
}
