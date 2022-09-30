/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/30 18:29:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, cmd);
}

int		heredoc(t_data *data, int cmd)
{
	t_parse *parse;

	parse = data->parse;
	(void)parse;
	(void)cmd;
	return (0);
	
}

void	exec_process(t_data *data)
{
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
			child_process(data, data->actual);
		if (data->pid > 0 && data->actual <= data->args)
		{
			if (heredoc(data, data->actual))
				wait(0);
			if (data->fd[1] > 2)
				close(data->fd[1]);
			if (data->oldfd > 2)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual += 1;
			exec_process(data);
		}
		wait(0);
	}
}

int	execution(t_data *data)
{
	// print_both(data);
	exec_process(data);
	close_pipes(data);
	return (1);
}
