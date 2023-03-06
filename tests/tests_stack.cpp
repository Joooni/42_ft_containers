/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_stack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:29:41 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/06 09:07:53 by jsubel           ###   ########.fr       */
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


		STACK_STD std1;
		STACK_STD std1_2;
		std::stack<int, std::vector<int> > std2;
		std::stack<int, std::vector<int> > std2_2;
		std::stack<int, std::deque<int> > std3;
		std::stack<int, std::deque<int> > std3_2;
		std::stack<int, std::list<int> > std4;
		std::stack<int, std::list<int> > std4_2;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
		{
			std1.push(i);
			std2.push(i+1);
			std3.push(i+2);
			std4.push(i+3);
		}
		for (int i = 0; i < 100000; i++)
		{
			std1_2.push(i * 2);
			std2_2.push(i * 42);
			std3_2.push(i * 3);
			std4_2.push(i * 7);
		}
		v1.push_back(std1.size());
		v1.push_back(std1.top());
		v1.push_back(std1_2.size());
		v1.push_back(std1_2.top());
		v1.push_back(std2.size());
		v1.push_back(std2.top());
		v1.push_back(std2_2.size());
		v1.push_back(std2_2.top());
		v1.push_back(std3.size());
		v1.push_back(std3.top());
		v1.push_back(std3_2.size());
		v1.push_back(std3_2.top());
		v1.push_back(std4.size());
		v1.push_back(std4.top());
		v1.push_back(std4_2.size());
		v1.push_back(std4_2.top());
		std1 = std1_2;
		std2 = std2_2;
		std3 = std3_2;
		std4 = std4_2;
		v1.push_back(std1.size());
		v1.push_back(std1.top());
		v1.push_back(std1_2.size());
		v1.push_back(std1_2.top());
		v1.push_back(std2.size());
		v1.push_back(std2.top());
		v1.push_back(std2_2.size());
		v1.push_back(std2_2.top());
		v1.push_back(std3.size());
		v1.push_back(std3.top());
		v1.push_back(std3_2.size());
		v1.push_back(std3_2.top());
		v1.push_back(std4.size());
		v1.push_back(std4.top());
		v1.push_back(std4_2.size());
		v1.push_back(std4_2.top());
		TIMER_STD;


		STACK_FT ft1;
		STACK_FT ft1_2;
		ft::stack<int, std::vector<int> > ft2;
		ft::stack<int, std::vector<int> > ft2_2;
		ft::stack<int, std::deque<int> > ft3;
		ft::stack<int, std::deque<int> > ft3_2;
		ft::stack<int, std::list<int> > ft4;
		ft::stack<int, std::list<int> > ft4_2;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
		{
			ft1.push(i);
			ft2.push(i+1);
			ft3.push(i+2);
			ft4.push(i+3);
		}
		for (int i = 0; i < 100000; i++)
		{
			ft1_2.push(i * 2);
			ft2_2.push(i * 42);
			ft3_2.push(i * 3);
			ft4_2.push(i * 7);
		}
		v2.push_back(ft1.size());
		v2.push_back(ft1.top());
		v2.push_back(ft1_2.size());
		v2.push_back(ft1_2.top());
		v2.push_back(ft2.size());
		v2.push_back(ft2.top());
		v2.push_back(ft2_2.size());
		v2.push_back(ft2_2.top());
		v2.push_back(ft3.size());
		v2.push_back(ft3.top());
		v2.push_back(ft3_2.size());
		v2.push_back(ft3_2.top());
		v2.push_back(ft4.size());
		v2.push_back(ft4.top());
		v2.push_back(ft4_2.size());
		v2.push_back(ft4_2.top());
		ft1 = ft1_2;
		ft2 = ft2_2;
		ft3 = ft3_2;
		ft4 = ft4_2;
		v2.push_back(ft1.size());
		v2.push_back(ft1.top());
		v2.push_back(ft1_2.size());
		v2.push_back(ft1_2.top());
		v2.push_back(ft2.size());
		v2.push_back(ft2.top());
		v2.push_back(ft2_2.size());
		v2.push_back(ft2_2.top());
		v2.push_back(ft3.size());
		v2.push_back(ft3.top());
		v2.push_back(ft3_2.size());
		v2.push_back(ft3_2.top());
		v2.push_back(ft4.size());
		v2.push_back(ft4.top());
		v2.push_back(ft4_2.size());
		v2.push_back(ft4_2.top());
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms " << (fttime > 20 * stdtime ? "\033[31m KO!" : "\033[32m OK!") << END << std::endl;
		compareVectors(v1, v2);
		std::cout << std::endl;
	}
	TESTHEAD(nbr_tests++)
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Testing stack push and pop:" << std::endl << END;
		std::vector<int> v1;
		std::vector<int> v2;

		STACK_STD std1;
		std::stack<int, std::vector<int> > std2;
		std::stack<int, std::deque<int> > std3;
		std::stack<int, std::list<int> > std4;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
		{
			std1.push(i);
			std2.push(i+1);
			std3.push(i+2);
			std4.push(i+3);
		}
		v1.push_back(std1.size());
		v1.push_back(std2.size());
		v1.push_back(std3.size());
		v1.push_back(std4.size());
		v1.push_back(std1.top());
		v1.push_back(std2.top());
		v1.push_back(std3.top());
		v1.push_back(std4.top());
		for (int i = 0; i < 99000; i++)
		{
			std1.pop();
			std2.pop();
			std3.pop();
			std4.pop();
		}
		v1.push_back(std1.size());
		v1.push_back(std2.size());
		v1.push_back(std3.size());
		v1.push_back(std4.size());
		v1.push_back(std1.top());
		v1.push_back(std2.top());
		v1.push_back(std3.top());
		v1.push_back(std4.top());
		TIMER_STD;

		STACK_FT ft1;
		ft::stack<int, std::vector<int> > ft2;
		ft::stack<int, std::deque<int> > ft3;
		ft::stack<int, std::list<int> > ft4;
		TIMER_START;
		for (int i = 0; i < 100000; i++)
		{
			ft1.push(i);
			ft2.push(i+1);
			ft3.push(i+2);
			ft4.push(i+3);
		}
		v2.push_back(ft1.size());
		v2.push_back(ft2.size());
		v2.push_back(ft3.size());
		v2.push_back(ft4.size());
		v2.push_back(ft1.top());
		v2.push_back(ft2.top());
		v2.push_back(ft3.top());
		v2.push_back(ft4.top());
		for (int i = 0; i < 99000; i++)
		{
			ft1.pop();
			ft2.pop();
			ft3.pop();
			ft4.pop();
		}
		v2.push_back(ft1.size());
		v2.push_back(ft2.size());
		v2.push_back(ft3.size());
		v2.push_back(ft4.size());
		v2.push_back(ft1.top());
		v2.push_back(ft2.top());
		v2.push_back(ft3.top());
		v2.push_back(ft4.top());
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
