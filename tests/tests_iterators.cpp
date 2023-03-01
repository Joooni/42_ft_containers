/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_iterators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:45:13 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/01 11:34:19 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include "../map.hpp"
#include "../colors.hpp"
#include "test_utils.hpp"

#include <map>
#include <functional>
#include <list>
#include <vector>
#include <stdlib.h>




int main(void)
{
	t_timeval start;
	int stdtime;
	int fttime;

	int nbr_test = 1;
	TESTHEAD(nbr_test++);
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "STD" << END << std::endl;
		std::vector<int> vec_std;
		for (unsigned int i = 0; i < 500000; ++i)
			vec_std.push_back(i);
		TIMER_START;
		std::vector<int>::iterator std_It = vec_std.begin();
		std::vector<int>::iterator std_ItE = vec_std.end();
		std::vector<int>::reverse_iterator std_ItR = vec_std.rbegin();
		std::vector<int>::reverse_iterator std_ItRE = vec_std.rend();
		std::cout << "It  == ItRE: " << ((std_It == std_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((std_ItR.base() == std_ItE) ? "true" : "false") << std::endl;
		std::cout << "It  <= ItRE: " << ((std_It <= std_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "It  > ItRE: " << ((std_It > std_ItRE.base()) ? "true" : "false") << std::endl;
		std_It += 5;
		--std_ItRE;
		--std_ItRE;
		--std_ItRE;
		--std_ItRE;
		--std_ItRE;
		std::cout << "It:\t" << *std_It << "\tItE:\t" << *(std_ItE - 1) << std::endl;
		std::cout << "ItR:\t" << *std_ItR << "\tItRE:\t" << *(std_ItRE - 1) << std::endl;
		std::cout << "It[5]:\t\t\t" << (std_It[5]) << std::endl;
		std::cout << "vec_std.begin()[113560]:\t" << vec_std.begin()[113560] << std::endl;
		std::cout << "vec_std.rbegin()[113560]:\t" << vec_std.rbegin()[113560] << std::endl;
		TIMER_STD;

		std::cout << COLOR_YELLOW << COLOR_FAINT << "FT" << END << std::endl;
		ft::vector<int> vec_ft;
		for (unsigned int i = 0; i < 500000; ++i)
			vec_ft.push_back(i);
		TIMER_START;
		ft::vector<int>::iterator ft_It = vec_ft.begin();
		ft::vector<int>::iterator ft_ItE = vec_ft.end();
		ft::vector<int>::reverse_iterator ft_ItR = vec_ft.rbegin();
		ft::vector<int>::reverse_iterator ft_ItRE = vec_ft.rend();
		std::cout << "It  == ItRE: " << ((ft_It == ft_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((ft_ItR.base() == ft_ItE) ? "true" : "false") << std::endl;
		std::cout << "It  <= ItRE: " << ((ft_It <= ft_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "It  > ItRE: " << ((ft_It > ft_ItRE.base()) ? "true" : "false") << std::endl;
		ft_It += 5;
		--ft_ItRE;
		--ft_ItRE;
		--ft_ItRE;
		--ft_ItRE;
		--ft_ItRE;
		std::cout << "It:\t" << *ft_It << "\tItE:\t" << *(ft_ItE - 1) << std::endl;
		std::cout << "ItR:\t" << *ft_ItR << "\tItRE:\t" << *(ft_ItRE - 1) << std::endl;
		std::cout << "It[5]:\t\t\t" << (ft_It[5]) << std::endl;
		std::cout << "vec_ft.begin()[113560]:\t\t" << vec_ft.begin()[113560] << std::endl;
		std::cout << "vec_ft.rbegin()[113560]:\t" << vec_ft.rbegin()[113560] << std::endl;
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
	}
	TESTHEAD(nbr_test++);
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "bidirectional iterator demonstrated on a map" << END << std::endl;
		std::cout << COLOR_YELLOW << COLOR_FAINT << "STD" << END << std::endl;
		std::map<int, const char> map_std;
		for (unsigned int i = 0; i < 500000; ++i)
			map_std.insert(std::pair<int, const char>(i, 'a' + (i % 26)));
		TIMER_START;
		std::map<int, const char>::iterator std_It(map_std.begin());
		std::map<int, const char>::iterator std_ItE = map_std.end();
		std::map<int, const char>::reverse_iterator std_ItR = map_std.rbegin();
		std::map<int, const char>::reverse_iterator std_ItRE = map_std.rend();
		std::cout << "It  == ItRE: " << ((std_It == std_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((std_ItR.base() == std_ItE) ? "true" : "false") << std::endl;
		++std_It;
		++std_It;
		++std_It;
		--std_ItE;
		--std_ItE;
		--std_ItE;
		++std_ItR;
		++std_ItR;
		++std_ItR;
		--std_ItRE;
		--std_ItRE;
		--std_ItRE;
		std::cout << "It:\t" << (*std_It).first << "/" << (*std_It).second << "\tItE:\t" << (*std_ItE).first << "/" << (*std_ItE).second  << std::endl;
		std::cout << "ItR:\t" << (*std_ItR).first << "/" << (*std_ItR).second << "\tItRE:\t" << (*std_ItRE).first << "/" << (*std_ItRE).second << std::endl;
		TIMER_STD;

		std::cout << COLOR_YELLOW << COLOR_FAINT << "FT" << END << std::endl;
		ft::map<int, const char> map_ft;
		for (unsigned int i = 0; i < 500000; ++i)
			map_ft.insert(ft::pair<int, const char>(i, 'a' + (i % 26)));
		TIMER_START;
		ft::map<int, const char>::iterator ft_It(map_ft.begin());
		ft::map<int, const char>::iterator ft_ItE = map_ft.end();
		ft::map<int, const char>::reverse_iterator ft_ItR = map_ft.rbegin();
		ft::map<int, const char>::reverse_iterator ft_ItRE = map_ft.rend();
		std::cout << "It  == ItRE: " << ((ft_It == ft_ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((ft_ItR.base() == ft_ItE) ? "true" : "false") << std::endl;
		++ft_It;
		++ft_It;
		++ft_It;
		--ft_ItE;
		--ft_ItE;
		--ft_ItE;
		++ft_ItR;
		++ft_ItR;
		++ft_ItR;
		--ft_ItRE;
		--ft_ItRE;
		--ft_ItRE;
		std::cout << "It:\t" << (*ft_It).first << "/" << (*ft_It).second << "\tItE:\t" << (*ft_ItE).first << "/" << (*ft_ItE).second  << std::endl;
		std::cout << "ItR:\t" << (*ft_ItR).first << "/" << (*ft_ItR).second << "\tItRE:\t" << (*ft_ItRE).first << "/" << (*ft_ItRE).second << std::endl;
		TIMER_FT;

		std::cout << "STD:\t" << stdtime << "ms\nFT:\t" << fttime << "ms\n";
	}
}
