NAME	=	minishell
SRCS	=	exec_func/exec_func.c tokenizer/tokenizer.c tokenizer/expand.c tokenizer/error.c\
			utils/split.c parser.c\
			readline/readline.c\
			map/map.c
OBJS	=	$(SRCS:%.c=%.o)
CC  	=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RLDIR	=	$(shell brew --prefix readline)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -L$(RLDIR)/lib -I$(RLDIR)/include -o $(NAME) -lreadline -lft

debug:$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
