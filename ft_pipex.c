/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:15:03 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 15:16:39 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_child_process(t_cmd *config, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_check_pipe(config, i);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	pipe_execute(t_cmd *config)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < config->npipe)
	{
		ft_child_process(config, i);
		i++;
	}
	dup2(config->stdout_clone, STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		ft_check_pipe(config, i);
	else
		waitpid(-1, NULL, 0);
	config->npipe = 0;
	dup2(config->stdin_clone, STDIN_FILENO);
	return (1);
}

int	red_pipe_execute(int file, t_cmd *config)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < config->npipe)
	{
		ft_child_process(config, i);
		i++;
	}
	dup2(file, STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		ft_check_pipe(config, i);
	else
		wait(NULL);
	config->npipe = 0;
	dup2(config->stdin_clone, STDIN_FILENO);
	dup2(config->stdout_clone, STDOUT_FILENO);
	close(file);
	return (1);
}
