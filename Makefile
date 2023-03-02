# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 09:18:29 by jsubel            #+#    #+#              #
#    Updated: 2023/03/02 17:11:53 by jsubel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_containers

COMPILER	= c++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic

all: intra iterator vector map set


intra:
	${COMPILER} ${CFLAGS} main_intra.cpp -o test_intra.out && ./test_intra.out aaaaaaaa

iterator:
	${COMPILER} ${CFLAGS} tests/tests_iterator.cpp -o test_iterator.out && leaks --atExit -- ./test_iterator.out

vector:
	${COMPILER} ${CFLAGS} tests/tests_vector.cpp -o test_vector.out && leaks --atExit -- ./test_vector.out

map:
	${COMPILER} ${CFLAGS} tests/tests_map.cpp -o test_map.out && leaks --atExit -- ./test_map.out

set:
	${COMPILER} ${CFLAGS} tests/tests_set.cpp -o test_set.out && leaks --atExit -- ./test_set.out

stack:
	${COMPILER} ${CFLAGS} tests/tests_stack.cpp -o test_stack.out && ./test_stack.out


clean:
	rm -rf

fclean:	clean
