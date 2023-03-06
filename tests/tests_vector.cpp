/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_vector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:26:19 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/06 10:34:15 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include <functional>
#include <vector>
#include <stdlib.h>
#include "test_utils.hpp"
#define VEC_STD		std::vector<int>
#define VEC_FT		ft::vector<int>

int main()
{
	int nbr_tests = 1;
	t_timeval start;
	int stdtime;
	int fttime;


	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector constructors (insertion one by one, by range, copy, empty):" << END << std::endl;

		TIMER_START;
		VEC_STD std_empty;
		VEC_STD std_size(1000000);
		VEC_STD std_filled(1000000, 58008);
		VEC_STD std_copyconstructed(std_filled);
		VEC_STD std_rangeconstructed(std_filled.begin(), std_filled.end());
		TIMER_STD;

		TIMER_START;
		VEC_FT ft_empty;
		VEC_FT ft_size(1000000);
		VEC_FT ft_filled(1000000, 58008);
		VEC_FT ft_copyconstructed(ft_filled);
		VEC_FT ft_rangeconstructed(ft_filled.begin(), ft_filled.end());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;


		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing assignment operations (operator=, assign):" << END << std::endl;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2(1000000);
		VEC_STD std3(1000000, 58008);
		VEC_STD std4;
		VEC_STD std5(1000000, 5317717);
		VEC_STD std6;

		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		v1.push_back(std3.size());
		v1.push_back(std3.capacity());
		v1.push_back(std4.size());
		v1.push_back(std4.capacity());
		v1.push_back(std5.size());
		v1.push_back(std5.capacity());
		v1.push_back(std6.size());
		v1.push_back(std6.capacity());
		TIMER_START;
		std1 = std2;
		std3 = std4;
		std5.assign(100, 58008);
		std6.assign(std2.begin() + 1000, std2.end() - 1000);
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		v1.push_back(std3.size());
		v1.push_back(std3.capacity());
		v1.push_back(std4.size());
		v1.push_back(std4.capacity());
		v1.push_back(std5.size());
		v1.push_back(std5.capacity());
		v1.push_back(std6.size());
		v1.push_back(std6.capacity());

		VEC_FT ft1;
		VEC_FT ft2(1000000);
		VEC_FT ft3(1000000, 58008);
		VEC_FT ft4;
		VEC_FT ft5(1000000, 5317717);
		VEC_FT ft6;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		v2.push_back(ft3.size());
		v2.push_back(ft3.capacity());
		v2.push_back(ft4.size());
		v2.push_back(ft4.capacity());
		v2.push_back(ft5.size());
		v2.push_back(ft5.capacity());
		v2.push_back(ft6.size());
		v2.push_back(ft6.capacity());
		TIMER_START;
		ft1 = ft2;
		ft3 = ft4;
		ft5.assign(100, 58008);
		ft6.assign(ft2.begin() + 1000, ft2.end() - 1000);
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		v2.push_back(ft3.size());
		v2.push_back(ft3.capacity());
		v2.push_back(ft4.size());
		v2.push_back(ft4.capacity());
		v2.push_back(ft5.size());
		v2.push_back(ft5.capacity());
		v2.push_back(ft6.size());
		v2.push_back(ft6.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;


		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing element access operations (at, operator[], front, back, data):" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		TIMER_START;
		v1.push_back(std1.at(100));
		v1.push_back(std1.at(200));
		v1.push_back(std1.at(0));
		v1.push_back(std1.at(58008));
		v1.push_back(std1[100]);
		v1.push_back(std1[200]);
		v1.push_back(std1[0]);
		v1.push_back(std1[58008]);
		try
		{
			v1.push_back(std1.at(100005));
		}
		catch(const std::out_of_range &oor)
		{
			v1.push_back(-1);
		}
		try
		{
			v1.push_back(std1[100005]);
		}
		catch(const std::out_of_range &oor)
		{
			v1.push_back(-1);
		}
		v1.push_back(std1.front());
		v1.push_back(std1.back());
		v1.push_back(&std1[0] == std1.data());
		TIMER_STD;

		VEC_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		TIMER_START;
		v2.push_back(ft1.at(100));
		v2.push_back(ft1.at(200));
		v2.push_back(ft1.at(0));
		v2.push_back(ft1.at(58008));
		v2.push_back(ft1[100]);
		v2.push_back(ft1[200]);
		v2.push_back(ft1[0]);
		v2.push_back(ft1[58008]);
		try
		{
			v2.push_back(ft1.at(100005));
		}
		catch(const std::out_of_range &oor)
		{
			v2.push_back(-1);
		}
		try
		{
			v2.push_back(ft1[100005]);
		}
		catch(const std::out_of_range &oor)
		{
			v2.push_back(-1);
		}
		v2.push_back(ft1.front());
		v2.push_back(ft1.back());
		v2.push_back(&ft1[0] == ft1.data());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing Capacity operations (empty, size, max_size, reserve, capacity):" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2(100000, 58008);
		TIMER_START;
		v1.push_back(std1.empty());
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std1.max_size());
		std1.reserve(100);
		v1.push_back(std1.empty());
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std1.max_size());
		v1.push_back(std2.empty());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		v1.push_back(std2.max_size());
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);
		std2.reserve(120000);
		v1.push_back(std2.empty());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		v1.push_back(std2.max_size());
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);
		TIMER_STD;

		VEC_FT ft1;
		VEC_FT ft2(100000, 58008);
		TIMER_START;
		v2.push_back(ft1.empty());
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft1.max_size());
		ft1.reserve(100);
		v2.push_back(ft1.empty());
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft1.max_size());
		v2.push_back(ft2.empty());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		v2.push_back(ft2.max_size());
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);
		ft2.reserve(120000);
		v2.push_back(ft2.empty());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		v2.push_back(ft2.max_size());
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector clear:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2;

		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		TIMER_START;
		std1.clear();
		std2.clear();
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);

		VEC_FT ft1;
		VEC_FT ft2;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		TIMER_START;
		ft1.clear();
		ft2.clear();
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector insert: single insert" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2;
		TIMER_START;
		for (int i = 0; i < 100; i++)
		{
			std1.insert(std1.begin(), i);
			std2.insert(std2.end(), i);
		}
		v1.push_back(*std1.insert(std1.begin(), -1));
		v1.push_back(*std1.insert(std1.begin() + 12, -1));
		v1.push_back(*std1.insert(std1.end(), -1));
		v1.push_back(*std1.insert(std1.end() - 51, -1));
		TIMER_STD;
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());

		VEC_FT ft1;
		VEC_FT ft2;
		TIMER_START;
		for (int i = 0; i < 100; i++)
		{
			ft1.insert(ft1.begin(), i);
			ft2.insert(ft2.end(), i);
		}
		v2.push_back(*ft1.insert(ft1.begin(), -1));
		v2.push_back(*ft1.insert(ft1.begin() + 12, -1));
		v2.push_back(*ft1.insert(ft1.end(), -1));
		v2.push_back(*ft1.insert(ft1.end() - 51, -1));
		TIMER_FT;
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector insert: count insert" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		for (int i = 0; i < 10000; i++)
			std1.insert(std1.begin(), i);
		TIMER_START;
		for (int i = 0; i < 500; i++)
			std1.insert(std1.begin() + i, 10, -1);
		std1.insert(std1.begin() + 10, 1000000, 58008);
		TIMER_STD;
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());

		VEC_FT ft1;
		for (int i = 0; i < 10000; i++)
			ft1.insert(ft1.begin(), i);
		TIMER_START;
		for (int i = 0; i < 500; i++)
			ft1.insert(ft1.begin() + i, 10, -1);
		ft1.insert(ft1.begin() + 10, 1000000, 58008);
		TIMER_FT;
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector insert: range insert" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2;
		VEC_STD std3;
		for (int i = 0; i < 12345; i++)
		{
			std1.insert(std1.begin(), i);
		}
		TIMER_START;
		std2.insert(std2.begin(), std1.begin(), std1.end());
		std3.insert(std3.begin(), std2.begin() + 100, std2.end() - 100);
		TIMER_STD;
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);
		for (VEC_STD::iterator it = std3.begin(); it != std3.end(); it++)
			v1.push_back(*it);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		v1.push_back(std3.size());
		v1.push_back(std3.capacity());

		VEC_FT ft1;
		VEC_FT ft2;
		VEC_FT ft3;
		for (int i = 0; i < 12345; i++)
		{
			ft1.insert(ft1.begin(), i);
		}
		TIMER_START;
		ft2.insert(ft2.begin(), ft1.begin(), ft1.end());
		ft3.insert(ft3.begin() ,ft2.begin() + 100, ft2.end() - 100);
		TIMER_FT;
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);
		for (VEC_FT::iterator it = ft3.begin(); it != ft3.end(); it++)
			v2.push_back(*it);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		v2.push_back(ft3.size());
		v2.push_back(ft3.capacity());


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}

	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector erase: single erase" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		TIMER_START;
		while (std1.size() > 1)
			v1.push_back(*std1.erase(std1.begin()));
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);

		VEC_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		TIMER_START;
		while (ft1.size() > 1)
			v2.push_back(*ft1.erase(ft1.begin()));
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector erase: range erase" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		TIMER_START;
		v1.push_back(*std1.erase(std1.begin(), std1.begin() + 25));
		v1.push_back(*std1.erase(std1.begin() + 100, std1.begin() + 2135));
		v1.push_back(*std1.erase(std1.begin() + 5, std1.begin() + 6));
		v1.push_back(*std1.erase(std1.begin() + 5, std1.begin() + 5));
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		std1.erase(std1.end() - 1000, std1.end());
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		std1.erase(std1.begin(), std1.end());
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());

		VEC_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		TIMER_START;
		v2.push_back(*ft1.erase(ft1.begin(), ft1.begin() + 25));
		v2.push_back(*ft1.erase(ft1.begin() + 100, ft1.begin() + 2135));
		v2.push_back(*ft1.erase(ft1.begin() + 5, ft1.begin() + 6));
		v2.push_back(*ft1.erase(ft1.begin() + 5, ft1.begin() + 5));
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		ft1.erase(ft1.end() - 1000, ft1.end());
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		ft1.erase(ft1.begin(), ft1.end());
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;

		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector push_back:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		TIMER_STD;
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());

		VEC_FT ft1;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		TIMER_FT;
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector pop_back:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		for (int i = 0; i < 100000; i++)
			std1.push_back(i);
		TIMER_START;
		while (std1.size() > 10)
			std1.pop_back();
		TIMER_STD;
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());

		VEC_FT ft1;
		for (int i = 0; i < 100000; i++)
			ft1.push_back(i);
		TIMER_START;
		while (ft1.size() > 10)
			ft1.pop_back();
		TIMER_FT;
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector resize:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1(100, 58008);
		VEC_STD std2(10000, 58008);
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);
		TIMER_START;
		std1.resize(1000);
		std2.resize(1000);
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.capacity());
		v1.push_back(std2.size());
		v1.push_back(std2.capacity());
		for (VEC_STD::iterator it = std1.begin(); it != std1.end(); it++)
			v1.push_back(*it);
		for (VEC_STD::iterator it = std2.begin(); it != std2.end(); it++)
			v1.push_back(*it);

		VEC_FT ft1(100, 58008);
		VEC_FT ft2(10000, 58008);
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);
		TIMER_START;
		ft1.resize(1000);
		ft2.resize(1000);
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.capacity());
		v2.push_back(ft2.size());
		v2.push_back(ft2.capacity());
		for (VEC_FT::iterator it = ft1.begin(); it != ft1.end(); it++)
			v2.push_back(*it);
		for (VEC_FT::iterator it = ft2.begin(); it != ft2.end(); it++)
			v2.push_back(*it);


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing vector swap:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD	std1;
		VEC_STD	std2;
		for (int i = 0; i < 10000; i++)
		{
			std1.push_back(i);
			std2.push_back(10000 - i);
		}
		VEC_STD::iterator it_std1 = std1.begin();
		VEC_STD::iterator it_std2 = std2.begin();
		int &ref_std1 = std1.front();
		int &ref_std2 = std2.front();
		v1.push_back((it_std1 == std1.begin()));
		v1.push_back((it_std1 == std2.begin()));
		v1.push_back((it_std2 == std1.begin()));
		v1.push_back((it_std2 == std2.begin()));
		v1.push_back((ref_std1 == std1.front()));
		v1.push_back((ref_std1 == std2.front()));
		v1.push_back((ref_std2 == std1.front()));
		v1.push_back((ref_std2 == std2.front()));
		TIMER_START;
		std1.swap(std2);
		TIMER_STD;
		v1.push_back((it_std1 == std1.begin()));
		v1.push_back((it_std1 == std2.begin()));
		v1.push_back((it_std2 == std1.begin()));
		v1.push_back((it_std2 == std2.begin()));
		v1.push_back((ref_std1 == std1.front()));
		v1.push_back((ref_std1 == std2.front()));
		v1.push_back((ref_std2 == std1.front()));
		v1.push_back((ref_std2 == std2.front()));

		VEC_FT	ft1;
		VEC_FT	ft2;
		for (int i = 0; i < 10000; i++)
		{
			ft1.push_back(i);
			ft2.push_back(10000 - i);
		}
		VEC_FT::iterator it_ft1 = ft1.begin();
		VEC_FT::iterator it_ft2 = ft2.begin();
		int &ref_ft1 = ft1.front();
		int &ref_ft2 = ft2.front();
		v2.push_back((it_ft1 == ft1.begin()));
		v2.push_back((it_ft1 == ft2.begin()));
		v2.push_back((it_ft2 == ft1.begin()));
		v2.push_back((it_ft2 == ft2.begin()));
		v2.push_back((ref_ft1 == ft1.front()));
		v2.push_back((ref_ft1 == ft2.front()));
		v2.push_back((ref_ft2 == ft1.front()));
		v2.push_back((ref_ft2 == ft2.front()));
		TIMER_START;
		ft1.swap(ft2);
		TIMER_FT;
		v2.push_back((it_ft1 == ft1.begin()));
		v2.push_back((it_ft1 == ft2.begin()));
		v2.push_back((it_ft2 == ft1.begin()));
		v2.push_back((it_ft2 == ft2.begin()));
		v2.push_back((ref_ft1 == ft1.front()));
		v2.push_back((ref_ft1 == ft2.front()));
		v2.push_back((ref_ft2 == ft1.front()));
		v2.push_back((ref_ft2 == ft2.front()));


		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing relational operations:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		VEC_STD std1;
		VEC_STD std2;

		TIMER_START;
		v1.push_back((std1 == std2));
		v1.push_back((std1 != std2));
		v1.push_back((std1 < std2));
		v1.push_back((std1 <= std2));
		v1.push_back((std1 > std2));
		v1.push_back((std1 >= std2));
		std1.push_back(58008);
		v1.push_back((std1 == std2));
		v1.push_back((std1 != std2));
		v1.push_back((std1 < std2));
		v1.push_back((std1 <= std2));
		v1.push_back((std1 > std2));
		v1.push_back((std1 >= std2));
		std2.push_back(58008);
		v1.push_back((std1 == std2));
		v1.push_back((std1 != std2));
		v1.push_back((std1 < std2));
		v1.push_back((std1 <= std2));
		v1.push_back((std1 > std2));
		v1.push_back((std1 >= std2));
		std1.push_back(-58008);
		v1.push_back((std1 == std2));
		v1.push_back((std1 != std2));
		v1.push_back((std1 < std2));
		v1.push_back((std1 <= std2));
		v1.push_back((std1 > std2));
		v1.push_back((std1 >= std2));
		std1.erase(std1.begin());
		v1.push_back((std1 == std2));
		v1.push_back((std1 != std2));
		v1.push_back((std1 < std2));
		v1.push_back((std1 <= std2));
		v1.push_back((std1 > std2));
		v1.push_back((std1 >= std2));
		TIMER_STD;

		VEC_FT ft1;
		VEC_FT ft2;

		TIMER_START;
		v2.push_back((ft1 == ft2));
		v2.push_back((ft1 != ft2));
		v2.push_back((ft1 < ft2));
		v2.push_back((ft1 <= ft2));
		v2.push_back((ft1 > ft2));
		v2.push_back((ft1 >= ft2));
		ft1.push_back(58008);
		v2.push_back((ft1 == ft2));
		v2.push_back((ft1 != ft2));
		v2.push_back((ft1 < ft2));
		v2.push_back((ft1 <= ft2));
		v2.push_back((ft1 > ft2));
		v2.push_back((ft1 >= ft2));
		ft2.push_back(58008);
		v2.push_back((ft1 == ft2));
		v2.push_back((ft1 != ft2));
		v2.push_back((ft1 < ft2));
		v2.push_back((ft1 <= ft2));
		v2.push_back((ft1 > ft2));
		v2.push_back((ft1 >= ft2));
		ft1.push_back(-58008);
		v2.push_back((ft1 == ft2));
		v2.push_back((ft1 != ft2));
		v2.push_back((ft1 < ft2));
		v2.push_back((ft1 <= ft2));
		v2.push_back((ft1 > ft2));
		v2.push_back((ft1 >= ft2));
		ft1.erase(ft1.begin());
		v2.push_back((ft1 == ft2));
		v2.push_back((ft1 != ft2));
		v2.push_back((ft1 < ft2));
		v2.push_back((ft1 <= ft2));
		v2.push_back((ft1 > ft2));
		v2.push_back((ft1 >= ft2));
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}

}
