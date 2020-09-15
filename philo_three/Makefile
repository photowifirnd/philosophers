NAME = philo_three

CC = gcc

FLAGS = -Wall -Werror -Wextra -I -g

LIBLINK = -lpthread

SRCS = main.c common.c set_initial.c primitive_living.c monitors.c messages.c sem.c

OBJS = $(SRCS:.c=.o)

%o:	%c
	$(CC) $(FLAGS) -c $<

ALL:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBLINK) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	rm -rf $(OBJS) $(NAME)

re:	fclean $(NAME)

.PHONY:	clean fclean
