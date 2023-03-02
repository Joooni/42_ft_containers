/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_set.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:30:28 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/02 14:31:53 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../set.hpp"
#include <functional>
#include <vector>
#include <set>
#include <stdlib.h>
#include "test_utils.hpp"
#define SET_STD		std::set<int>
#define SET_FT		ft::set<int>

template<typename set>
void PushToVector(set *st, std::vector<int> *v)
{
	v->push_back(st->size());
	for (typename set::iterator it = st->begin(); it != st->end(); it++)
		v->push_back(*it);
	v->push_back(st->size());
}

int main(void)
{
	int nbr_tests = 1;
	t_timeval start;
	int stdtime;
	int fttime;

	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing set constructors (insertion one by one, by range, copy, empty):" << END << std::endl;

		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.insert(i);
		TIMER_START;
		SET_STD std2(std1.begin(), std1.end());
		SET_STD std3(std2);
		SET_STD std4;
		TIMER_STD;
		PushToVector<SET_STD>(&std2, &v1);
		PushToVector<SET_STD>(&std3, &v1);
		PushToVector<SET_STD>(&std4, &v1);

		SET_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.insert(i);
		TIMER_START;
		SET_FT ft2(ft1.begin(), ft1.end());
		SET_FT ft3(ft2);
		SET_FT ft4;
		TIMER_FT;
		PushToVector<SET_FT >(&ft2, &v2);
		PushToVector<SET_FT >(&ft3, &v2);
		PushToVector<SET_FT >(&ft4, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing assignment operator:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.insert(i);
		TIMER_START;
		SET_STD std2;
		SET_STD std3;
		SET_STD std4;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);
		PushToVector<SET_STD>(&std3, &v1);
		PushToVector<SET_STD>(&std4, &v1);
		std2 = std1;
		std4 = std3;
		TIMER_STD;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);
		PushToVector<SET_STD>(&std3, &v1);
		PushToVector<SET_STD>(&std4, &v1);

		SET_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.insert(i);
		TIMER_START;
		SET_FT ft2;
		SET_FT ft3;
		SET_FT ft4;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);
		PushToVector<SET_FT>(&ft3, &v2);
		PushToVector<SET_FT>(&ft4, &v2);
		ft2 = ft1;
		ft4 = ft3;
		TIMER_FT;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);
		PushToVector<SET_FT>(&ft3, &v2);
		PushToVector<SET_FT>(&ft4, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime  << "ms\n";
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing Capacity functions:" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		SET_STD std2;
		for (int i = 0; i < 20000; i++)
			std1.insert(i);
		TIMER_START;
		v1.push_back(std1.empty());
		v1.push_back(std1.size());
		v1.push_back(std2.empty());
		v1.push_back(std2.size());
		TIMER_STD;

		SET_FT ft1;
		SET_FT ft2;
		for (int i = 0; i < 20000; i++)
			ft1.insert(i);
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

		SET_STD std1;
		SET_STD std2;
		for (int i = 0; i < 20000; i++)
			std1.insert(i);
		PushToVector(&std1, &v1);
		PushToVector(&std2, &v1);
		TIMER_START;
		std1.clear();
		std2.clear();
		TIMER_STD;
		PushToVector(&std1, &v1);
		PushToVector(&std2, &v1);

		SET_FT ft1;
		SET_FT ft2;
		for (int i = 0; i < 20000; i++)
			ft1.insert(i);
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

		SET_STD std1;
		SET_STD std2;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);
		std::pair<SET_STD::iterator, bool> stdpair;
		TIMER_START;
		for (int i = 0; i < 20000; i++)
		{
			stdpair = std1.insert(i);
			v1.push_back(*stdpair.first);
			v1.push_back(stdpair.second);
			stdpair = std2.insert(5000000 - i);
			v1.push_back(*stdpair.first);
			v1.push_back(stdpair.second);
		}
		for (int i = 25; i < 500; i++)
		{
			stdpair = std1.insert(i);
			v1.push_back(*stdpair.first);
			v1.push_back(stdpair.second);
			stdpair = std2.insert(5000000 - i);
			v1.push_back(*stdpair.first);
			v1.push_back(stdpair.second);
		}
		TIMER_STD;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);

		SET_FT ft1;
		SET_FT ft2;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);
		ft::pair<SET_FT::iterator, bool> ftpair;
		TIMER_START;
		for (int i = 0; i < 20000; i++)
		{
			ftpair = ft1.insert(i);
			v2.push_back(*ftpair.first);
			v2.push_back(ftpair.second);
			ftpair = ft2.insert(5000000 - i);
			v2.push_back(*ftpair.first);
			v2.push_back(ftpair.second);
		}
		for (int i = 25; i < 500; i++)
		{
			ftpair = ft1.insert(i);
			v2.push_back(*ftpair.first);
			v2.push_back(ftpair.second);
			// std::cout << COLOR_YELLOW << COLOR_FAINT << (ftpair.second ? "true" : "false") << std::endl << END <<;
			ftpair = ft2.insert(5000000 - i);
			v2.push_back(*ftpair.first);
			v2.push_back(ftpair.second);
		}
		TIMER_FT;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing inserts: range" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		SET_STD std2;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);
		for (int i = 0; i < 100000; i++)
			std1.insert(i);
		TIMER_START;
		std2.insert(std1.begin(), std1.end());
		TIMER_STD;
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);

		SET_FT ft1;
		SET_FT ft2;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);
		for (int i = 0; i < 100000; i++)
			ft1.insert(i);
		TIMER_START;
		ft2.insert(ft1.begin(), ft1.end());
		TIMER_FT;
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing erase: from iterator (single and range)" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.insert(i);
		SET_STD::iterator it_std1 = std1.begin();
		SET_STD::iterator it_std2 = std1.begin();
		PushToVector<SET_STD>(&std1, &v1);
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
		PushToVector<SET_STD>(&std1, &v1);

		SET_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.insert(i);
		SET_FT::iterator it_ft1 = ft1.begin();
		SET_FT::iterator it_ft2 = ft1.begin();
		PushToVector<SET_FT>(&ft1, &v2);
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
		PushToVector<SET_FT>(&ft1, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing erase: key" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		for (int i = 0; i < 500000; i++)
			std1.insert(i);
		PushToVector<SET_STD>(&std1, &v1);
		TIMER_START;
		for (int i = 0; i < 100000; i++)
			v1.push_back(std1.erase(i * 2));
		TIMER_STD;
		PushToVector<SET_STD>(&std1, &v1);

		SET_FT ft1;
		for (int i = 0; i < 500000; i++)
			ft1.insert(i);
		PushToVector<SET_FT>(&ft1, &v2);
		TIMER_START;
		for (int i = 0; i < 100000; i++)
			v2.push_back(ft1.erase(i * 2));
		TIMER_FT;
		PushToVector<SET_FT>(&ft1, &v2);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing map swap:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		SET_STD std2;
		for (int i = 0; i < 100; i++)
		{
			std1.insert(i);
			std2.insert(100 - i);
		}
		SET_STD::iterator it_std1 = std1.begin();
		SET_STD::iterator it_std2 = std2.begin();
		v1.push_back(it_std1 == std1.begin());
		v1.push_back(it_std2 == std1.begin());
		v1.push_back(it_std1 == std2.begin());
		v1.push_back(it_std2 == std2.begin());
	PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);
		TIMER_START;
		std1.swap(std2);
		TIMER_STD;
		v1.push_back(it_std1 == std1.begin());
		v1.push_back(it_std2 == std1.begin());
		v1.push_back(it_std1 == std2.begin());
		v1.push_back(it_std2 == std2.begin());
		PushToVector<SET_STD>(&std1, &v1);
		PushToVector<SET_STD>(&std2, &v1);

		SET_FT ft1;
		SET_FT ft2;
		for (int i = 0; i < 100; i++)
		{
			ft1.insert(i);
			ft2.insert(100 - i);
		}
		SET_FT::iterator it_ft1 = ft1.begin();
		SET_FT::iterator it_ft2 = ft2.begin();
		v2.push_back(it_ft1 == ft1.begin());
		v2.push_back(it_ft2 == ft1.begin());
		v2.push_back(it_ft1 == ft2.begin());
		v2.push_back(it_ft2 == ft2.begin());
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);
		TIMER_START;
		ft1.swap(ft2);
		TIMER_FT;
		v2.push_back(it_ft1 == ft1.begin());
		v2.push_back(it_ft2 == ft1.begin());
		v2.push_back(it_ft1 == ft2.begin());
		v2.push_back(it_ft2 == ft2.begin());
		PushToVector<SET_FT>(&ft1, &v2);
		PushToVector<SET_FT>(&ft2, &v2);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing Lookup functions (count ,find, equal_range, lower_bound, upper_bound):" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		SET_STD std1;
		for (int i = 0; i < 10000; i++)
			std1.insert(i);
		TIMER_START;
		for (int i = -5; i < 5; i++)
			v1.push_back(std1.count(i));
		for (int i = -5; i < 5; i++)
			v1.push_back(*std1.find(i));
		for (int i = -1; i < 10; i++)
		{
			v1.push_back(*std1.equal_range(i * 5).first);
			v1.push_back(*std1.equal_range(i * 5).first);
			v1.push_back(*std1.equal_range(i * 5).second);
			v1.push_back(*std1.equal_range(i * 5).second);
			v1.push_back(*std1.lower_bound(i * 5));
			v1.push_back(*std1.lower_bound(i * 5));
			v1.push_back(*std1.upper_bound(i * 5));
			v1.push_back(*std1.upper_bound(i * 5));
		}
		v1.push_back(std1.equal_range(1500).first == std1.end());
		v1.push_back(std1.equal_range(1500).second  == std1.end());
		v1.push_back(std1.lower_bound(1500) == std1.end());
		v1.push_back(std1.upper_bound(1500) == std1.end());
		TIMER_STD;

		SET_FT ft1;
		for (int i = 0; i < 10000; i++)
			ft1.insert(i);
		TIMER_START;
		for (int i = -5; i < 5; i++)
			v2.push_back(ft1.count(i));
		for (int i = -5; i < 5; i++)
			v2.push_back(*ft1.find(i));
		for (int i = -1; i < 10; i++)
		{
			v2.push_back(*ft1.equal_range(i * 5).first);
			v2.push_back(*ft1.equal_range(i * 5).first);
			v2.push_back(*ft1.equal_range(i * 5).second);
			v2.push_back(*ft1.equal_range(i * 5).second);
			v2.push_back(*ft1.lower_bound(i * 5));
			v2.push_back(*ft1.lower_bound(i * 5));
			v2.push_back(*ft1.upper_bound(i * 5));
			v2.push_back(*ft1.upper_bound(i * 5));
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

		SET_STD std1;
		SET_STD std2;
		TIMER_START;
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std1.insert(1);
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(1);
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(3);
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		std2.insert(4);
		v1.push_back(std1 == std2);
		v1.push_back(std1 != std2);
		v1.push_back(std1 < std2);
		v1.push_back(std1 <= std2);
		v1.push_back(std1 > std2);
		v1.push_back(std1 >= std2);
		TIMER_STD;

		SET_FT ft1;
		SET_FT ft2;
		TIMER_START;
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft1.insert(1);
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(1);
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(3);
		v2.push_back(ft1 == ft2);
		v2.push_back(ft1 != ft2);
		v2.push_back(ft1 < ft2);
		v2.push_back(ft1 <= ft2);
		v2.push_back(ft1 > ft2);
		v2.push_back(ft1 >= ft2);
		ft2.insert(4);
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



	// 	std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
	// 	compareVectors(v1, v2);
	// 	std::cout << std::endl;
	// }

}
