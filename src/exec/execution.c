/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/10 21:29:53 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execution(t_data *data)
{
	if (data->actual == data->args && is_builtin(data))
	{
		data->code = exec_builtout(data);
		return (data->code);
	}
	else
	{
		exec_process(data);
		data->code = getcode(data);
		close_pipes(data);
		unlink(data->tmp);
	}
	return (data->code);
}

void	exec_process(t_data *data)
{
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid[data->actual - 1] = fork();
		if (data->pid[data->actual - 1] < 0)
			return ;
		if (data->pid[data->actual - 1] == 0)
			child_process(data, data->actual);
		if (data->pid[data->actual - 1] > 0 && data->actual <= data->args)
		{	
			if (data->exec[data->actual - 1].heredoc)
				wait(0);
			if (data->fd[1] > 2)
				close(data->fd[1]);
			if (data->oldfd > 2)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual += 1;
			exec_process(data);
		}
	}
}

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, cmd);
	else
		exit(EXIT_FAILURE);
}

int	handle_fd(t_data *data, int cmd)
{
	if (!fd_infile(data, cmd))
		return (0);
	if (!fd_outfile(data, cmd))
		return (0);
	return (1);
}

void	execute(t_data *data, int cmdnb)
{
	char	**cmd;
	char	**bash;
	int		builtin;

	cmd = getcmd(data, cmdnb);
	if (cmd[0][0] == '\0')
		return (err_return(cmd));
	if (!cmd)
		exit(EXIT_FAILURE);
	builtin = trybuiltin(data, cmd);
	if (builtin >= 0)
		exit(builtin);
	if (ft_strlen(cmd[0]) > 0 && !is_path(cmd[0]))
		cmd[0] = setpath(cmd[0], data->env);
	if (!cmd[0] || access(cmd[0], X_OK != 0))
		return (err_return(cmd));
	if (execve(cmd[0], cmd, data->env) == -1)
	{
		if (access(cmd[0], X_OK != 0))
			perror(cmd[0]);
		else
		{
			bash = test(cmd);
			if (execve(bash[0], bash, data->env) == -1)
				exit(EXIT_FAILURE);
		}
	}
}