/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:29:25 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 17:56:21 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_right(t_cmd *config)
{
	int	fd;

	fd = open(config->cmd_line[config->num_cmd - 1],
			O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (config->npipe > 0)
	{
		return (red_pipe_execute(fd, config));
	}
	dup2(fd, STDOUT_FILENO);
	cmd_single(config);
	close(fd);
	dup2(config->stdout_clone, STDOUT_FILENO);
	return (1);
}

int	double_right(t_cmd *config)
{
	pid_t	pid;
	int		fd;

	fd = open(config->cmd_line[config->num_cmd - 1],
			O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (config->npipe > 0)
	{
		return (red_pipe_execute(fd, config));
	}
	pid = fork();
	if (pid == -1)
		return (0);
	dup2(fd, STDOUT_FILENO);
	if (pid == 0)
		execve(ft_pathfinder(config->cmd_line[0], config->envp),
			args_build(config, 0), config->envp);
	else
		wait(NULL);
	dup2(config->stdout_clone, STDOUT_FILENO);
	return (1);
}

int	single_left(t_cmd *config)
{
	int	fd;

	fd = open(config->cmd_line[config->num_cmd - 1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	cmd_single(config);
	close(fd);
	dup2(config->stdin_clone, STDIN_FILENO);
	return (1);
}

int	double_left(t_cmd *config)
{
	int		fd;
	char	*delimiter;
	char	*lines;

	config->st = 1;
	delimiter = config->cmd_line[config->num_cmd - 1];
	fd = open(".tmp", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (config->st)
	{
		lines = readline(">");
		if (ft_strcmp(lines, delimiter) == 0)
		{
			config->st = 0;
			break ;
		}
		ft_putstr_fd(lines, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	fd = open(".tmp", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	cmd_single(config);
	close(fd);
	dup2(config->stdin_clone, STDIN_FILENO);
	return (1);
}
