# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cschabra <cschabra@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/05 16:15:02 by cschabra      #+#    #+#                  #
#    Updated: 2023/07/05 17:06:52 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= philo
CFLAGS= -Wall -Wextra -Werror $(HEADERS) #-0fast #-fsanitize=address 

HEADERS= -I include

CFILES= test.c

OBJECTS= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) -o $(NAME) -lm $(CFLAGS) $(CFILES)

clean:
	rm  -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS = -g
debug: re

.PHONY: all clean fclean re debug