# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 09:18:29 by jsubel            #+#    #+#              #
#    Updated: 2023/02/15 09:37:58 by jsubel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_containers

COMPILER	= c++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic


map:
	${COMPILER} ${CFLAGS} tests/tests_map.cpp

iterator:
	${COMPILER} ${CFLAGS} tests/tests_iterators.cpp -o test_iterator.out && ./test_iterator.out

clean:
	rm -rf

fclean:	clean
