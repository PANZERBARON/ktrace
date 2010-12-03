CC       =    /usr/bin/gcc
SRC      =    my_ktrace.c          \
              my_ktrace_optparse.c \
              my_ktrace_utils.c
NAME     =    my_ktrace
CFLAGS   =    -W -Wall -Wstrict-prototypes -ansi -pedantic
RM       =    rm -rf
OBJS     =    $(SRC:.c=.o)


$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all: $(NAME)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
