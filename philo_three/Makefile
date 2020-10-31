NAME = philo_three

HEADER = philo.h

FLAGS = -Wall -Wextra -Werror

SRCS = main.c printstr.c utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
		@$(CC) $(FLAGS) -c $< -o $@

clean:
		@rm -rf $(OBJS)

fclean:
		@rm -rf $(OBJS) $(NAME)

re: fclean all

test1:
		@MAKE re
		@MAKE clean
		./philo_three 5 800 200 200
		@MAKE fclean

test2:
		@MAKE re
		@MAKE clean
		./philo_three 5 800 200 200 7
		@MAKE fclean

test3:
		@MAKE re
		@MAKE clean
		./philo_three 4 410 200 200
		@MAKE fclean

test4:
		@MAKE re
		@MAKE clean
		./philo_three 4 310 200 100
		@MAKE fclean

.PHONY: all fclean clean re test1 test2 test3 test4