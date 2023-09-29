# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/09/14 16:03:51 by cschabra      #+#    #+#                  #
#    Updated: 2023/09/29 14:52:23 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= philo
CFLAGS= -Wall -Wextra -Werror $(HEADERS) #-0fast

HEADERS= -I include

CFILES= ${shell find src -iname "*.c"}

OBJECTS= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) -o $(NAME) -pthread $(CFLAGS) $(CFILES)

clean:
	rm  -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g #-fsanitize=thread -fsanitize=address
debug: re

.PHONY: all clean fclean re debug