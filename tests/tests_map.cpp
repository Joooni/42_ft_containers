/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:16:57 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/27 15:29:42 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <functional>
#include <vector>
#include <map>
#include <stdlib.h>
#include "test_utils.hpp"
#define MAP_STD		std::map<int, int>
#define MAP_FT		ft::map<int, int>
#define TIMESTART	gettimeofday(&start, NULL)
#define TIMER_STD	stdtime = gettime(start)
#define TIMER_FT	fttime = gettime(start)

template<typename map>
void PushToVector(map *mp, std::vector<int> *v)
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

	TESTHEAD(nbr_tests++)
	{
		std::cout << "Testing Iterators:" << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;
		MAP_STD std1;
		MAP_STD::iterator std_it;
		MAP_STD::const_iterator std_cit;
		MAP_STD::reverse_iterator std_rit;
		MAP_STD::const_reverse_iterator std_crit;
		for (int i = 0, j = 0; i < 10; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMESTART;
		std_it = std1.begin();
		std_cit = std1.begin();
		std_rit = std1.rbegin();
		std_crit = std1.rbegin();
		v1.push_back(std_it == std_cit);
		v1.push_back(std_rit == std_crit);
		while (std_it != std1.end())
		{
			v1.push_back(std_it->first);
			v1.push_back(std_it->second);
			std_it++;
		}
		--std_it;
		while (std_it != std1.begin())
		{
			v1.push_back(std_it->first);
			v1.push_back(std_it->second);
			std_it--;
		}
		while (std_cit != std1.end())
		{
			v1.push_back(std_cit->first);
			v1.push_back(std_cit->second);
			std_cit++;
		}
		--std_cit;
		while (std_cit != std1.begin())
		{
			v1.push_back(std_cit->first);
			v1.push_back(std_cit->second);
			std_cit--;
		}
		while (std_rit != std1.rend())
		{
			v1.push_back(std_rit->first);
			v1.push_back(std_rit->second);
			std_rit++;
		}
		--std_rit;
		while (std_rit != std1.rbegin())
		{
			v1.push_back(std_rit->first);
			v1.push_back(std_rit->second);
			std_rit--;
		}
		while (std_crit != std1.rend())
		{
			v1.push_back(std_crit->first);
			v1.push_back(std_crit->second);
			std_crit++;
		}
		--std_crit;
		while (std_crit != std1.rbegin())
		{
			v1.push_back(std_crit->first);
			v1.push_back(std_crit->second);
			std_crit--;
		}
		TIMER_STD;

		std::cout << "MAP PART" << std::endl;
		MAP_FT ft1;
		MAP_FT::iterator ft_it;
		MAP_FT::const_iterator ft_cit;
		MAP_FT::reverse_iterator ft_rit;
		MAP_FT::const_reverse_iterator ft_crit;
		for (int i = 0, j = 0; i < 10; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMESTART;
		ft_it = ft1.begin();
		ft_cit = ft1.begin();
		ft_rit = ft1.rbegin();
		ft_crit = ft1.rbegin();
		v2.push_back(ft_it == ft_cit);
		v2.push_back(ft_rit == ft_crit);
		while (ft_it != ft1.end())
		{
			v2.push_back(ft_it->first);
			v2.push_back(ft_it->second);
			ft_it++;
		}
		--ft_it;
		while (ft_it != ft1.begin())
		{
			v2.push_back(ft_it->first);
			v2.push_back(ft_it->second);
			ft_it--;
		}
		while (ft_cit != ft1.end())
		{
			v2.push_back(ft_cit->first);
			v2.push_back(ft_cit->second);
			ft_cit++;
		}
		--ft_cit;
		while (ft_cit != ft1.begin())
		{
			v2.push_back(ft_cit->first);
			v2.push_back(ft_cit->second);
			ft_cit--;
		}
		while (ft_rit != ft1.rend())
		{
			v2.push_back(ft_rit->first);
			v2.push_back(ft_rit->second);
			ft_rit++;
		}
		--ft_rit;
		while (ft_rit != ft1.rbegin())
		{
			v2.push_back(ft_rit->first);
			v2.push_back(ft_rit->second);
			ft_rit--;
		}
		while (ft_crit != ft1.rend())
		{
			v2.push_back(ft_crit->first);
			v2.push_back(ft_crit->second);
			ft_crit++;
		}
		--ft_crit;
		while (ft_crit != ft1.rbegin())
		{
			v2.push_back(ft_crit->first);
			v2.push_back(ft_crit->second);
			ft_crit--;
		}
		TIMER_FT;


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}

	TESTHEAD(nbr_tests++);
	{
		std::cout << "Testing map constructors (insertion one by one, by range, copy, empty):" << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMESTART;
		MAP_STD std2(std1.begin(), std1.end());
		MAP_STD std3(std2);
		MAP_STD std4;
		TIMER_STD;
		PushToVector<MAP_STD>(&std2, &v1);
		PushToVector<MAP_STD>(&std3, &v1);
		PushToVector<MAP_STD>(&std4, &v1);

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMESTART;
		MAP_FT ft2(ft1.begin(), ft1.end());
		MAP_FT ft3(ft2);
		MAP_FT ft4;
		TIMER_FT;
		PushToVector<MAP_FT >(&ft2, &v2);
		PushToVector<MAP_FT >(&ft3, &v2);
		PushToVector<MAP_FT >(&ft4, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << "Testing assignment operator:" << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMESTART;
		MAP_STD std2;
		MAP_STD std3;
		MAP_STD std4;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);
		PushToVector<MAP_STD>(&std3, &v1);
		PushToVector<MAP_STD>(&std4, &v1);
		std2 = std1;
		std4 = std3;
		TIMER_STD;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);
		PushToVector<MAP_STD>(&std3, &v1);
		PushToVector<MAP_STD>(&std4, &v1);

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMESTART;
		MAP_FT ft2;
		MAP_FT ft3;
		MAP_FT ft4;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);
		PushToVector<MAP_FT>(&ft3, &v2);
		PushToVector<MAP_FT>(&ft4, &v2);
		ft2 = ft1;
		ft4 = ft3;
		TIMER_FT;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);
		PushToVector<MAP_FT>(&ft3, &v2);
		PushToVector<MAP_FT>(&ft4, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 26; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMESTART;
		v1.push_back(std1.at(5));
		v1.push_back(std1.at(8));
		v1.push_back(std1.at(0));
		v1.push_back(std1.at(0));
		v1.push_back(std1.at(8));
		try
		{
			v1.push_back(std1.at(30));
		}
		catch (const std::out_of_range &out_of_range_exception)
		{
			v1.push_back(-1);
		}
		v1.push_back(std1[5]);
		v1.push_back(std1[8]);
		v1.push_back(std1[0]);
		v1.push_back(std1[0]);
		v1.push_back(std1[8]);
		TIMER_STD;

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 26; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMESTART;
		v2.push_back(ft1.at(5));
		v2.push_back(ft1.at(8));
		v2.push_back(ft1.at(0));
		v2.push_back(ft1.at(0));
		v2.push_back(ft1.at(8));
		try
		{
			v2.push_back(ft1.at(30));
		}
		catch (const std::out_of_range &out_of_range_exception)
		{
			v2.push_back(-1);
		}
		v2.push_back(ft1[5]);
		v2.push_back(ft1[8]);
		v2.push_back(ft1[0]);
		v2.push_back(ft1[0]);
		v2.push_back(ft1[8]);
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;

	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << "Testing:" << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}

}
