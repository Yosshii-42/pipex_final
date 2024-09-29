NAME 	= pipex
SRCS	= src/main.c \
		  src/set_env.c \
		  src/make_command.c \
		  src/open_files.c \
		  src/process.c \
		  src/process_utils.c \
		  src/utils.c \
		  src/free.c
OBJS	= $(SRCS:.c=.o)
CC		= cc
FLAGS	= -Wall -Wextra -Werror
# FLAGS   += -fsanitize=address -g
HEADDIR	= ./pipex.h
LIBFT	= ./libft/libft.a

%.o:%.c
	$(CC) $(FLAGS) -I$(HEADDIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(FLAGS) -I. $(OBJS) $(LIBFT) -o $(NAME)

bonus: all

clean:
	make fclean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
