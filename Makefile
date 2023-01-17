NAME = minishell

CC		= gcc
RM		= rm -f
CFLAGS 	= -Wall -Wextra -Werror -Wno-unused-command-line-argument
READLINE = 		-L $(HOME)/homebrew/Cellar/readline/8.2.1/lib -I $(HOME)/homebrew/Cellar/readline/8.2.1/include -lreadline


SRC = mini.c \
		ft_atoi.c \
		ft_dollar_while.c \
		ft_export.c \
		ft_isdigit.c \
		ft_memcpy.c \
		ft_mini_utils.c \
		ft_parser.c \
		ft_pipex.c \
		ft_putchar.c \
		ft_quotes.c \
		ft_quotes_utils.c \
		ft_quotes_while.c \
		ft_red.c \
		ft_signal.c \
		ft_split.c \
		ft_strcat.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_substr.c \
		ft_utils_1.c \
		ft_utils_2.c \
		ft_utils_3.c \
		ft_utils.c 

OBJS = ${SRC:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE) -c $< -o ${<:.c=.o}


$(NAME): ${OBJS}
		$(CC) $(CFLAGS) $(READLINE) -o $(NAME) $(OBJS)

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY: clean fclean re bonus%  