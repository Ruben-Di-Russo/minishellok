#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#define SPACE_DELM ' '
#define PIPE_DELM '|'
#define DOUBLE_RIGHT_REDIRECTION '>>'
#define DOUBLE_LEFT_REDIRECTION '<<'

typedef struct s_cmd
{
	int		builtin_len;
	char	*line;
	char	**cmd_line;
	char	**cmd_args;
	char	**cmd_value;
	char	**builtin_cmd;
	char	**envp;
	int		npipe;
	char	*banner;
	char	**cmd_parser;
	int		num_cmd;
	int		stdout_clone;
	int		stdin_clone;
	char	*operator;
	int		red;
	int		last_cmd_position;
	char	*file;
	char	**arg_build;
	int		jump;
	char	*index_q;
	int		i;
	int		t;
	int		space;
	int		d;
	char	*exit_code;
	char	*dollar_tmp;
	char	*dollar_tmp2;
	int		find_x;
	int		st;
	int		cmd_i;
	char	*cmd_tmp;
	char	**cmd_tmp2;
	int		n_parser;
	char	*parser_tmp;
	int		parser_x;
	int		parser_y;
	int		parser_o;
	int		echo_i;
	int		echo_n;
	int		echo_t;
	int		echo_space;
	int		echo_time;
	char	*echo_tmp;

}	t_cmd;
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		builtin_exec(t_cmd *config);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_pathfinder(char *cmd, char **envp);
int		free_matrix(char **matrix);
void	ft_free_matrix(char **matrix);
char	*read_line(t_cmd *config);
int		double_right(t_cmd *config);
int		single_right(t_cmd *config);
int		single_left(t_cmd *config);
int		double_left(t_cmd *config);
int		ft_check(t_cmd *config);
int		ft_check_pipe(t_cmd *config, int i);
char	*operator(void);
int		cmd_execute(t_cmd *config);
char	**cmd_parser(t_cmd *config);
void	cmd_fill(t_cmd *config );
int		echo_fill(t_cmd *config, char *line, int i);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
int		pipe_execute(t_cmd *config);
int		red_pipe_execute(int file, t_cmd *config);
int		ft_process_red(t_cmd *config, int i);
int		cmd_single(t_cmd *config);
char	**args_build(t_cmd *config, int i);
int		ft_child_process(t_cmd *config, int i);
void	ft_clean(t_cmd *config);
int		cmd_execute(t_cmd *config);
int		cmd_prepare(t_cmd *config);
int		cmd_cd(char **args);
int		cmd_exit(char **args, t_cmd *config);
void	ft_argv_print(char **argv, char *type);
int		len_num_builtins(char **builtin_str);
char	**builtin_str(void);
int		builtin_func(char *cmd, char **args, t_cmd *config);
void	shell_init(t_cmd *config, char **envp);
void	shell_loop(t_cmd *config);
int		ft_export(char **args, t_cmd *config);
int		ft_isdigit(int c);
int		ft_matrix_len(char **mtx);
int		ft_unset(char **args, t_cmd *config);
int		cmd_unset(char **args, t_cmd *config);
char	*dollar(t_cmd *config, char *line, int time);
int		ft_isalpha(int c);
int		check_quotes(t_cmd *config, char *line, int pos);
char	*quote_index(void);
char	*find_dollar(char *line, int time, t_cmd *config);
char	*ft_strchr(const char *s, int c);
char	*find_envp(t_cmd *config, char *tmp);
int		ft_isprint(int c);
int		check_line(char *line);
int		ft_atoi(const char *str);
void	sighand(int sig);
void	sig_handling_set(int signals);
int		if_execute(t_cmd *config);
int		else_execute(t_cmd *config);
int		ft_isdigit(int c);
void	ft_checkunset(t_cmd *config, char *str);
char	**ft_set_envp(char **envp);
int		ft_ciack(char *tmp);
char	*mod_echo(char *line, t_cmd *config, int i);
void	cmd_if(t_cmd *config, char **tmp2);
void	null_space(t_cmd *config);
void	cmd_init(t_cmd *config);
void	parser_count(t_cmd *config);
void	count_if(t_cmd *config);
char	*find_tmp(t_cmd *config);
void	while_tmp(t_cmd *config);
char	*single_while(t_cmd *config, char *line, char *copy);
void	accrocchio_1(t_cmd *config);
char	*accrocchio_2(t_cmd *config, char *line, char *tmp);
char	*accrocchio_3(t_cmd *config, char *line, char *tmp);
void	accrocchio_4(t_cmd *config);
char	*dollar_while(t_cmd *config, char *line, char *copy);
char	*dollar_put(t_cmd *config, int time, char *line);
char	*dollar_double(t_cmd *config, char *line, char *copy);
char	*accrocchio_finale(t_cmd *config, char *line);

#endif