/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:01:31 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/02 11:26:59 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "../colors.hpp"
typedef struct timeval	t_timeval;

#define TESTHEAD(NBR)		std::cout << COLOR_YELLOW << std::string(20, '~') << "Test " << NBR << std::string(20, '~') << END << std::endl;
#define TIMER_START	gettimeofday(&start, NULL)
#define TIMER_STD	stdtime = gettime(start)
#define TIMER_FT	fttime = gettime(start)


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template<typename T>
void compareVectorsIndepth(std::vector<T> v1, std::vector<T> v2)
{
	int i = v1.size();
	int j = v2.size();
	std::cout << std::endl;

	if (i != j)
		std::cout << "\x1B[31m" << "SIZES ARE DIFFERENT" <<  "\033[0m";
	int n = std::min(i, j);
	for (i = 0; i < n; i++)
	{
		if (v1[i] != v2[i])
			std::cout << "Index: " << i << " \x1B[31m" << v1[i] << " : " << v2[i] <<  "\033[0m"<< std::endl;
	}
}
template<typename T>
void compareVectors(std::vector<T> v1, std::vector<T> v2)
{
	if (v1 == v2)
		std::cout << "\x1B[32m" << "OK" <<  "\033[0m";
	else
	{
		std::cout << "\x1B[31m" << "KO" <<  "\033[0m";
		compareVectorsIndepth<T>(v1, v2);
	}
}

int	gettime(t_timeval start)
{
	t_timeval	tv;
	int			time_diff;

	gettimeofday(&tv, NULL);
	time_diff = (tv.tv_sec - start.tv_sec) * 1000;
	time_diff += (tv.tv_usec - start.tv_usec) / 1000;
	return (time_diff);
}
