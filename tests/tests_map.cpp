/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:16:57 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/02 15:15:01 by jsubel           ###   ########.fr       */
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

	TESTHEAD(nbr_tests++);
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing map constructors (insertion one by one, by range, copy, empty):" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
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
		TIMER_START;
		MAP_FT ft2(ft1.begin(), ft1.end());
		MAP_FT ft3(ft2);
		MAP_FT ft4;
		TIMER_FT;
		PushToVector<MAP_FT >(&ft2, &v2);
		PushToVector<MAP_FT >(&ft3, &v2);
		PushToVector<MAP_FT >(&ft4, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing assignment operator:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
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
		TIMER_START;
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

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime  << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing element access:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 26; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
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
		TIMER_START;
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

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;

	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing Capacity functions:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		for (int i = 0, j = 0; i < 20000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
		v1.push_back(std1.empty());
		v1.push_back(std1.size());
		v1.push_back(std2.empty());
		v1.push_back(std2.size());
		TIMER_STD;

		MAP_FT ft1;
		MAP_FT ft2;
		for (int i = 0, j = 0; i < 20000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMER_START;
		v2.push_back(ft1.empty());
		v2.push_back(ft1.size());
		v2.push_back(ft2.empty());
		v2.push_back(ft2.size());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing clear:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		for (int i = 0, j = 0; i < 20000; i++, j++)
			std1.insert(std::make_pair(i,j));
		PushToVector(&std1, &v1);
		PushToVector(&std2, &v1);
		TIMER_START;
		std1.clear();
		std2.clear();
		TIMER_STD;
		PushToVector(&std1, &v1);
		PushToVector(&std2, &v1);

		MAP_FT ft1;
		MAP_FT ft2;
		for (int i = 0, j = 0; i < 20000; i++, j++)
			ft1.insert(ft::make_pair(i,j));
		PushToVector(&ft1, &v2);
		PushToVector(&ft2, &v2);
		TIMER_START;
		ft1.clear();
		ft2.clear();
		TIMER_FT;
		PushToVector(&ft1, &v2);
		PushToVector(&ft2, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing inserts: single" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);
		std::pair<MAP_STD::iterator, bool> stdpair;
		TIMER_START;
		for (int i = 0, j = 0; i < 20000; i++, j++)
		{
			stdpair = std1.insert(std::make_pair(i, j));
			v1.push_back(stdpair.first->first);
			v1.push_back(stdpair.first->second);
			v1.push_back(stdpair.second);
			stdpair = std2.insert(std::make_pair(500000 - i, 500000 - j));
			v1.push_back(stdpair.first->first);
			v1.push_back(stdpair.first->second);
			v1.push_back(stdpair.second);
		}
		for (int i = 25, j = 5; i < 500; i++, j++)
		{
			stdpair = std1.insert(std::make_pair(i, j));
			v1.push_back(stdpair.first->first);
			v1.push_back(stdpair.first->second);
			v1.push_back(stdpair.second);
			stdpair = std2.insert(std::make_pair(500000 - i, 500000 - j));
			v1.push_back(stdpair.first->first);
			v1.push_back(stdpair.first->second);
			v1.push_back(stdpair.second);
		}
		TIMER_STD;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);

		MAP_FT ft1;
		MAP_FT ft2;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);
		ft::pair<MAP_FT::iterator, bool> ftpair;
		TIMER_START;
		for (int i = 0, j = 0; i < 20000; i++, j++)
		{
			ftpair = ft1.insert(ft::make_pair(i, j));
			v2.push_back(ftpair.first->first);
			v2.push_back(ftpair.first->second);
			v2.push_back(ftpair.second);
			ftpair = ft2.insert(ft::make_pair(500000 - i, 500000 - j));
			v2.push_back(ftpair.first->first);
			v2.push_back(ftpair.first->second);
			v2.push_back(ftpair.second);
		}
		for (int i = 25, j = 5; i < 500; i++, j++)
		{
			ftpair = ft1.insert(ft::make_pair(i, j));
			v2.push_back(ftpair.first->first);
			v2.push_back(ftpair.first->second);
			v2.push_back(ftpair.second);
			// std::cout << COLOR_YELLOW << COLOR_FAINT << (ftpair.second ? "true" : "false") << std::endl << END <<;
			ftpair = ft2.insert(ft::make_pair(500000 - i, 500000 - j));
			v2.push_back(ftpair.first->first);
			v2.push_back(ftpair.first->second);
			v2.push_back(ftpair.second);
		}
		TIMER_FT;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing inserts: range" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
		std2.insert(std1.begin(), std1.end());
		TIMER_STD;
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);

		MAP_FT ft1;
		MAP_FT ft2;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);
		for (int i = 0, j = 0; i < 10000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMER_START;
		ft2.insert(ft1.begin(), ft1.end());
		TIMER_FT;
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing erase: from iterator (single and range)" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			std1.insert(std::make_pair(i, j));
		MAP_STD::iterator it_std1 = std1.begin();
		MAP_STD::iterator it_std2 = std1.begin();
		PushToVector<MAP_STD>(&std1, &v1);
		for (int i = 0; i < 500; i++)
		{
			++it_std1;
			++it_std2;
			++it_std2;
		}
		TIMER_START;
		std1.erase(std1.begin());
		std1.erase(it_std1, it_std2);
		TIMER_STD;
		PushToVector<MAP_STD>(&std1, &v1);

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 10000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		MAP_FT::iterator it_ft1 = ft1.begin();
		MAP_FT::iterator it_ft2 = ft1.begin();
		PushToVector<MAP_FT>(&ft1, &v2);
		for (int i = 0; i < 500; i++)
		{
			++it_ft1;
			++it_ft2;
			++it_ft2;
		}
		TIMER_START;
		ft1.erase(ft1.begin());
		ft1.erase(it_ft1, it_ft2);
		TIMER_FT;
		PushToVector<MAP_FT>(&ft1, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing erase: key" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 50000; i++, j++)
			std1.insert(std::make_pair(i, j));
		PushToVector<MAP_STD>(&std1, &v1);
		TIMER_START;
		for (int i = 0; i < 1000; i++)
			v1.push_back(std1.erase(i * 7));
		TIMER_STD;
		PushToVector<MAP_STD>(&std1, &v1);

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 50000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		PushToVector<MAP_FT>(&ft1, &v2);
		TIMER_START;
		for (int i = 0; i < 1000; i++)
			v2.push_back(ft1.erase(i * 7));
		TIMER_FT;
		PushToVector<MAP_FT>(&ft1, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing map swap:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		for (int i = 0, j = 100; i < 100; i++, j--)
		{
			std1.insert(std::make_pair(i, j));
			std2.insert(std::make_pair(j, i));
		}
		MAP_STD::iterator it_std1 = std1.begin();
		MAP_STD::iterator it_std2 = std2.begin();
		v1.push_back(it_std1 == std1.begin());
		v1.push_back(it_std2 == std1.begin());
		v1.push_back(it_std1 == std2.begin());
		v1.push_back(it_std2 == std2.begin());
	PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);
		TIMER_START;
		std1.swap(std2);
		TIMER_STD;
		v1.push_back(it_std1 == std1.begin());
		v1.push_back(it_std2 == std1.begin());
		v1.push_back(it_std1 == std2.begin());
		v1.push_back(it_std2 == std2.begin());
		PushToVector<MAP_STD>(&std1, &v1);
		PushToVector<MAP_STD>(&std2, &v1);

		MAP_FT ft1;
		MAP_FT ft2;
		for (int i = 0, j = 100; i < 100; i++, j--)
		{
			ft1.insert(ft::make_pair(i, j));
			ft2.insert(ft::make_pair(j, i));
		}
		MAP_FT::iterator it_ft1 = ft1.begin();
		MAP_FT::iterator it_ft2 = ft2.begin();
		v2.push_back(it_ft1 == ft1.begin());
		v2.push_back(it_ft2 == ft1.begin());
		v2.push_back(it_ft1 == ft2.begin());
		v2.push_back(it_ft2 == ft2.begin());
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);
		TIMER_START;
		ft1.swap(ft2);
		TIMER_FT;
		v2.push_back(it_ft1 == ft1.begin());
		v2.push_back(it_ft2 == ft1.begin());
		v2.push_back(it_ft1 == ft2.begin());
		v2.push_back(it_ft2 == ft2.begin());
		PushToVector<MAP_FT>(&ft1, &v2);
		PushToVector<MAP_FT>(&ft2, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing Lookup functions (count ,find, equal_range, lower_bound, upper_bound):" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		for (int i = 0, j = 0; i < 1000; i++, j++)
			std1.insert(std::make_pair(i, j));
		TIMER_START;
		for (int i = -5; i < 5; i++)
			v1.push_back(std1.count(i));
		for (int i = -5; i < 5; i++)
			v1.push_back(std1.find(i)->first);
		for (int i = -1; i < 10; i++)
		{
			v1.push_back(std1.equal_range(i * 5).first->first);
			v1.push_back(std1.equal_range(i * 5).first->second);
			v1.push_back(std1.equal_range(i * 5).second->first);
			v1.push_back(std1.equal_range(i * 5).second->second);
			v1.push_back(std1.lower_bound(i * 5)->first);
			v1.push_back(std1.lower_bound(i * 5)->second);
			v1.push_back(std1.upper_bound(i * 5)->first);
			v1.push_back(std1.upper_bound(i * 5)->second);
		}
		v1.push_back(std1.equal_range(1500).first == std1.end());
		v1.push_back(std1.equal_range(1500).second  == std1.end());
		v1.push_back(std1.lower_bound(1500) == std1.end());
		v1.push_back(std1.upper_bound(1500) == std1.end());
		TIMER_STD;

		MAP_FT ft1;
		for (int i = 0, j = 0; i < 1000; i++, j++)
			ft1.insert(ft::make_pair(i, j));
		TIMER_START;
		for (int i = -5; i < 5; i++)
			v2.push_back(ft1.count(i));
		for (int i = -5; i < 5; i++)
			v2.push_back(ft1.find(i)->first);
		for (int i = -1; i < 10; i++)
		{
			v2.push_back(ft1.equal_range(i * 5).first->first);
			v2.push_back(ft1.equal_range(i * 5).first->second);
			v2.push_back(ft1.equal_range(i * 5).second->first);
			v2.push_back(ft1.equal_range(i * 5).second->second);
			v2.push_back(ft1.lower_bound(i * 5)->first);
			v2.push_back(ft1.lower_bound(i * 5)->second);
			v2.push_back(ft1.upper_bound(i * 5)->first);
			v2.push_back(ft1.upper_bound(i * 5)->second);
		}
		v2.push_back(ft1.equal_range(1500).first == ft1.end());
		v2.push_back(ft1.equal_range(1500).second  == ft1.end());
		v2.push_back(ft1.lower_bound(1500) == ft1.end());
		v2.push_back(ft1.upper_bound(1500) == ft1.end());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing relational operators:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		MAP_STD std1;
		MAP_STD std2;
		TIMER_START;
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std1.insert(std::make_pair(1,2));
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(std::make_pair(1,2));
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(std::make_pair(3,2));
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(std::make_pair(4,3));
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		TIMER_STD;

		MAP_FT ft1;
		MAP_FT ft2;
		TIMER_START;
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft1.insert(ft::make_pair(1,2));
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(ft::make_pair(1,2));
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(ft::make_pair(3,2));
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(ft::make_pair(4,3));
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	// TESTHEAD(nbr_tests++)
	// {
	// 	std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing :" << std::endl << END;
	// 	std::vector<int> v1;
	// 	std::vector<int> v2;



	// 	std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
	// 	compareVectors(v1, v2);
	// 	std::cout << std::endl;
	// }

}
