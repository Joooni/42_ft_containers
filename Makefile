# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 09:18:29 by jsubel            #+#    #+#              #
#    Updated: 2023/02/06 09:21:28 by jsubel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_containers

COMPILER	= c++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic


map:
	${COMPILER} ${CFLAGS} tests/tests_map.cpp

clean:
	rm -rf

fclean:	clean
