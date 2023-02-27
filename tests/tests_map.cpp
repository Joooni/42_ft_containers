/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:16:57 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/27 12:02:26 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <functional>
#include <vector>
#include <map>
#include <stdlib.h>
#include "test_utils.hpp"
#define MAP_STD std::map<int, int>
#define MAP_FT ft::map<int, int>

template<typename map>
void pushtoVector(map *mp, std::vector<int> *v)
{
	v->push_back(mp->size());
	for (typename map::iterator it = mp->begin(); it != mp->end(); it++)
	{
		v->push_back(it->first);
		v->push_back(it->second);
	}
	v->push_back(mp->size());
}

int main(void)
{
	int nbr_tests = 1;
	t_timeval start;
	int stdtime;
	int fttime;
	TESTHEAD(nbr_tests++);
	{
		std::cout << "\nTesting map constructors (insertion one by one, by range, copy, empty):" << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 5; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		gettimeofday(&start, NULL);
		MAP_STD std2(std1.begin(), std1.end());
		MAP_STD std3(std2);
		MAP_STD std4;
		stdtime = gettime(start);
		pushtoVector<MAP_STD>(&std2, &v1);
		pushtoVector<MAP_STD>(&std3, &v1);
		pushtoVector<MAP_STD>(&std4, &v1);

		MAP_FT ft1;
		for (int i = 0, j = 5; i < 10000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		gettimeofday(&start, NULL);
		MAP_FT ft2(ft1.begin(), ft1.end());
		MAP_FT ft3(ft2);
		MAP_FT ft4;
		fttime = gettime(start);
		pushtoVector<MAP_FT >(&ft2, &v2);
		pushtoVector<MAP_FT >(&ft3, &v2);
		pushtoVector<MAP_FT >(&ft4, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
}
