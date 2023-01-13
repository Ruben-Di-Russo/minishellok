#include "minishell.h"


int ft_check(t_cmd *config)
{
//   char *s[10] = {config->cmd_line[0], config->cmd_args[0], config->cmd_value[0], NULL};
  
  if (config->cmd_line[0][0] == '/')
  {
	execve(config->cmd_line[0], args_build(config, 0), config->envp);
	return(1);
  }
  else
  {
	execve(ft_pathfinder(config->cmd_line[0], config->envp), args_build(config, 0), config->envp);
	return(1);
  }
  return(0);
}

int ft_check_pipe(t_cmd *config, int i)
{
  if (config->cmd_line[i][0] == '/')
  {
	execve(config->cmd_line[i], args_build(config, i), config->envp);
	ft_free_matrix(config->arg_build);
	return(1);
  }
  else
  {
	execve(ft_pathfinder(config->cmd_line[i], config->envp), args_build(config, i), config->envp);
	ft_free_matrix(config->arg_build);
	return(1);
  }
  return(0);
}

char **builtin_str(void)
{
	char *cmd;
	char **str;
	cmd = "cd exit export unset";
	str = ft_split(cmd, (char)SPACE_DELM);
	return (str);    
}


void  ft_clean(t_cmd *config){
  printf("start cleaning ... \n");
  config->red = 0;
  config->npipe = 0;
  free(config->line);
  free_matrix(config->cmd_parser);
//   ft_free_matrix(config->cmd_line);
//   ft_free_matrix(config->cmd_args);
//   ft_free_matrix(config->cmd_value);
  free_matrix(config->cmd_value);
  free_matrix(config->cmd_line);
  free_matrix(config->cmd_args);
}

void ft_free_matrix(char **matrix)
{
  int i;

  i = 0;
  if(!matrix)
	return ;
  while(matrix[i])
  {
	if(matrix[i]){
	  free(matrix[i]);
	}
	i++;
  }
}

char *operator(void)
{
	char *op;
	op = malloc(sizeof(char) * 3 + 1);
	op[0] = '|';
	op[1] = '>';
	op[2] = '<';
	op[3] = '\0';
	return (op);    
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 - *s2 == 0)
		{
			s1++;
			s2++;
		}
		else
		{
			return (*s1 - *s2);
		}
	}
	return (*s1 - *s2);
}

void ft_argv_print(char **argv, char *type)
{
  int i = 0;
  while (argv[i]){
	printf("%s argv print id %d : %s \n",type, i, argv[i]);
	i++;
  }
}

int builtin_func(char *cmd, char **args,t_cmd *config)
{
  if (ft_strcmp(cmd, "cd") == 0)
  {
	return (cmd_cd(args));
  }
  else if (ft_strcmp(cmd, "export") == 0)
	return (ft_export(args, config));
  else if (ft_strcmp(cmd, "exit") == 0)
	return (cmd_exit(args, config));
  else if (ft_strcmp(cmd, "unset") == 0)
	return (cmd_unset(args, config));    
  return (0);
}

char	*ft_pathfinder(char *cmd, char **envp)
{
	char	**mypaths;
	char	*pathnoslash;
	char	*pathinenv;
	char	*finalpath;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	pathinenv = envp[i] + 5;
	mypaths = ft_split(pathinenv, ':');
	i = 0;
	while (mypaths[i])
	{
		pathnoslash = ft_strjoin(mypaths[i], "/");
		finalpath = ft_strjoin(pathnoslash, cmd);
		free(pathnoslash);
		if (access(finalpath, F_OK) == 0)
			return (finalpath);
		free(finalpath);
		i++;
	}
	free_matrix(mypaths);
	return (NULL);
}

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

char *split_to_line(char **str){
	  int i;
	int count;
	char *line;
	i = 0;
	count = 0;
	while (str[i] != NULL){
		count += ft_strlen(str[i]);
		i++;
	}
	line = malloc( sizeof(char) * count + 1 );
	i = 0;
	while(str[i]){
		ft_strcat(line, str[i]);
		i++;
	}
	line[count] = '\0';
	return(line); 
}

int len_num_builtins(char **builtin_str)
{
  int i;
  i = 0;
  while(builtin_str[i])
  {
	i++;
  }
  return (i);
}

/*
  Builtin function implementations.
*/
int cmd_cd(char **args)
{
  // printf("val : %s \n", args[1]);
  if (args[0] == NULL)
  {
	fprintf(stderr, "expected argument to \"cd\"\n");
  } 
  else {
	if (chdir(args[0]) != 0) {
	  perror("shell");
	}
  }
  return 1;
}

int cmd_exit(char **args, t_cmd *config)
{
  ft_clean(config);
  free_matrix(config->envp);
  free_matrix(config->builtin_cmd);
//   free(config->cmd_parser);
//   free(config->cmd_line);
//   free(config->cmd_args);
//   free(config->cmd_value);
  free(config->operator);
  free(config->index_q);
  if(args[0])
	exit(ft_atoi(args[0]));
  exit(0);
}

int cmd_unset(char **args, t_cmd *config)
{
  return(ft_unset(args, config));
}