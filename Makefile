SRCS = 	srcs/main.c \
		srcs/utils/ft_notop.c srcs/utils/ft_strdup.c srcs/utils/print.c \
		srcs/parsing/lexer.c srcs/parsing/parser.c srcs/parsing/utils_parsing.c \
		srcs/signaux/prompt_sig.c \
		#srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_export.c srcs/builtins/ft_pdw.c srcs/builtins/ft_unset.c

C.O = ${SRCS:.c=.o}

H = includes/minishell.h
NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
DEBUG = -g
LEAK = -fsanitize=address

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(DEBUG) $(SRCS) -o $(NAME) -lreadline

leak :
	$(CC) $(FLAGS) $(LEAK) $(SRCS) -o leak -lreadline

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all
