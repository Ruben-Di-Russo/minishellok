/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-russ <rdi-russ@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:09 by rdi-russ          #+#    #+#             */
/*   Updated: 2023/01/16 14:56:31 by rdi-russ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(t_cmd *config)
{
	char	*line;

	line = readline(config->banner);
	if (!line[0] || !check_line(line))
	{
		while (!line[0] || !check_line(line))
			line = readline(config->banner);
	}
	else
		add_history(line);
	return (line);
}

void	shell_loop(t_cmd *config)
{
	int	status;

	status = 2;
	while (1)
	{
		sig_handling_set(1);
		if (status == 2)
			config->exit_code = "0";
		else if (status == 1)
			config->exit_code = "127";
		config->line = read_line(config);
		cmd_parser(config);
		cmd_fill(config);
		status = cmd_prepare(config);
		ft_clean(config);
	}
}

char	**args_build(t_cmd *config, int i)
{
	int	x;

	x = 0;
	config->arg_build = malloc(sizeof(char *) * 100);
	config->arg_build[x] = ft_strdup(config->cmd_line[i]);
	x++;
	if (config->cmd_args[i] && (ft_strcmp(config->cmd_args[i], "NULLO")))
	{
		config->arg_build[x] = ft_strdup(config->cmd_args[i]);
		x++;
	}
	else if ((config->cmd_args[i]
			&& !(ft_strcmp(config->cmd_args[i], "NULLO"))))
	{
		config->arg_build[x] = NULL;
		x++;
	}
	if (config->cmd_value[i])
	{
		config->arg_build[x] = ft_strdup(config->cmd_value[i]);
		x++;
	}
	config->arg_build[x] = NULL;
	return (config->arg_build);
}

void	shell_init(t_cmd *config, char **envp)
{
	config->envp = ft_set_envp(envp);
	config->npipe = 0;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
	config->banner = ft_strcat(getenv("USER"), "@minishell>");
	config->stdout_clone = dup(STDOUT_FILENO);
	config->stdin_clone = dup(STDIN_FILENO);
	config->operator = operator();
	config->index_q = quote_index();
	config->red = 0;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd	config;

	shell_init(&config, envp);
	shell_loop(&config);
	return (1);
}
