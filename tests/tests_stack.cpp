/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_stack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:29:41 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/02 17:16:34 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stack.hpp"
#include <functional>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <stdlib.h>
#include "test_utils.hpp"
#define STACK_STD	std::stack<int>
#define STACK_FT	ft::stack<int>

int main()
{
	int nbr_tests = 1;
	t_timeval start;
	int stdtime;
	int fttime;


	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing stack constructors:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		TIMER_START;
		STACK_STD std1;
		std::stack<int, std::vector<int> > std2;
		std::stack<int, std::deque<int> > std3;
		std::stack<int, std::list<int> > std4;
		v1.push_back(std1.size());
		v1.push_back(std2.size());
		v1.push_back(std3.size());
		v1.push_back(std4.size());
		TIMER_STD;

		TIMER_START;
		STACK_FT ft1;
		ft::stack<int, std::vector<int> > ft2;
		ft::stack<int, std::deque<int> > ft3;
		ft::stack<int, std::list<int> > ft4;
		v2.push_back(ft1.size());
		v2.push_back(ft2.size());
		v2.push_back(ft3.size());
		v2.push_back(ft4.size());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing stack operator= :" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		std::cout << "AAAAAAAA" << std::endl;
		STACK_STD std1;
		STACK_STD std1_a;
		std::stack<int, std::vector<int> > std2;
		std::stack<int, std::vector<int> > std2_a;
		std::stack<int, std::deque<int> > std3;
		std::stack<int, std::deque<int> > std3_a;
		std::stack<int, std::list<int> > std4;
		std::stack<int, std::list<int> > std4_a;
		for (int i = 0; i < 123512; i++)
		{
			std1.push(i + 1);
			std2.push(i + 2);
			std3.push(i + 3);
			std4.push(i + 4);
		}
		v1.push_back(std1.size());
		v1.push_back(std1.top());
		v1.push_back(std1_a.size());
		v1.push_back(std1_a.top());
		v1.push_back(std2.size());
		v1.push_back(std2.top());
		v1.push_back(std2_a.size());
		v1.push_back(std2_a.top());
		v1.push_back(std3.size());
		v1.push_back(std3.top());
		v1.push_back(std3_a.size());
		v1.push_back(std3_a.top());
		v1.push_back(std4.size());
		v1.push_back(std4.top());
		v1.push_back(std4_a.size());
		v1.push_back(std4_a.top());
		TIMER_START;
		std1_a = std1;
		std2_a = std2;
		std3_a = std3;
		std4_a = std4;
		TIMER_STD;
		v1.push_back(std1.size());
		v1.push_back(std1.top());
		v1.push_back(std1_a.size());
		v1.push_back(std1_a.top());
		v1.push_back(std2.size());
		v1.push_back(std2.top());
		v1.push_back(std2_a.size());
		v1.push_back(std2_a.top());
		v1.push_back(std3.size());
		v1.push_back(std3.top());
		v1.push_back(std3_a.size());
		v1.push_back(std3_a.top());
		v1.push_back(std4.size());
		v1.push_back(std4.top());
		v1.push_back(std4_a.size());
		v1.push_back(std4_a.top());

		STACK_FT ft1;
		STACK_FT ft1_a;
		ft::stack<int, std::vector<int> > ft2;
		ft::stack<int, std::vector<int> > ft2_a;
		ft::stack<int, std::deque<int> > ft3;
		ft::stack<int, std::deque<int> > ft3_a;
		ft::stack<int, std::list<int> > ft4;
		ft::stack<int, std::list<int> > ft4_a;
		for (int i = 0; i < 123512; i++)
		{
			ft1.push(i + 1);
			ft2.push(i + 2);
			ft3.push(i + 3);
			ft4.push(i + 4);
		}
		v2.push_back(ft1.size());
		v2.push_back(ft1.top());
		v2.push_back(ft1_a.size());
		v2.push_back(ft1_a.top());
		v2.push_back(ft2.size());
		v2.push_back(ft2.top());
		v2.push_back(ft2_a.size());
		v2.push_back(ft2_a.top());
		v2.push_back(ft3.size());
		v2.push_back(ft3.top());
		v2.push_back(ft3_a.size());
		v2.push_back(ft3_a.top());
		v2.push_back(ft4.size());
		v2.push_back(ft4.top());
		v2.push_back(ft4_a.size());
		v2.push_back(ft4_a.top());
		TIMER_START;
		ft1_a = ft1;
		ft2_a = ft2;
		ft3_a = ft3;
		ft4_a = ft4;
		TIMER_FT;
		v2.push_back(ft1.size());
		v2.push_back(ft1.top());
		v2.push_back(ft1_a.size());
		v2.push_back(ft1_a.top());
		v2.push_back(ft2.size());
		v2.push_back(ft2.top());
		v2.push_back(ft2_a.size());
		v2.push_back(ft2_a.top());
		v2.push_back(ft3.size());
		v2.push_back(ft3.top());
		v2.push_back(ft3_a.size());
		v2.push_back(ft3_a.top());
		v2.push_back(ft4.size());
		v2.push_back(ft4.top());
		v2.push_back(ft4_a.size());
		v2.push_back(ft4_a.top());


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
