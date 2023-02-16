/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_iterators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:45:13 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/16 10:15:07 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include "../map.hpp"
#include "../colors.hpp"

#include <functional>
#include <time.h>
#include <list>
#include <stdlib.h>




int main(void)
{
	int nbr_test = 1;
	TESTHEAD(nbr_test++);
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "random access iterator demonstrated on a vector" << END << std::endl;
		ft::vector<int> vec;
		for (unsigned int i = 0; i < 50; ++i)
			vec.push_back(i);
		ft::vector<int>::iterator It = vec.begin();
		ft::vector<int>::iterator ItE = vec.end();
		ft::vector<int>::reverse_iterator ItR = vec.rbegin();
		ft::vector<int>::reverse_iterator ItRE = vec.rend();
		std::cout << COLOR_YELLOW << COLOR_FAINT << "end and rend should point to garbage values since they point to values after end/before begin" << END << std::endl;
		std::cout << "It:\t" << *It << "\tItE:\t" << *ItE << std::endl;
		std::cout << "ItR:\t" << *ItR << "\tItRE:\t" << *ItRE << std::endl;
		std::cout << COLOR_YELLOW << COLOR_FAINT << "thus, if you take the value just before those, they should be begin and end, respectively" << END << std::endl;
		std::cout << "It:\t" << *It << "\tItE:\t" << *(ItE - 1) << std::endl;
		std::cout << "ItR:\t" << *ItR << "\tItRE:\t" << *(ItRE - 1) << std::endl;
		std::cout << "It  == ItRE: " << ((It == ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((ItR.base() == ItE) ? "true" : "false") << std::endl;
		std::cout << "It  <= ItRE: " << ((It <= ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "It  > ItRE: " << ((It > ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Now we increase It by 5 and decrement ItRE by the same amount" << END << std::endl;
		It += 5;
		--ItRE;
		--ItRE;
		--ItRE;
		--ItRE;
		--ItRE;
		std::cout << "It:\t" << *It << "\tItE:\t" << *(ItE - 1) << std::endl;
		std::cout << "ItR:\t" << *ItR << "\tItRE:\t" << *(ItRE - 1) << std::endl;
		std::cout << COLOR_YELLOW << COLOR_FAINT << "We can even access any value with the [] operator, starting at the current iterator" << END << std::endl;
		std::cout << "It[5]:\t" << (It[5]) << std::endl;
		std::cout << "vec.begin()[10]:\t" << vec.begin()[10] << std::endl;
		std::cout << "ItR[10]:\t" << (ItR[10]) << std::endl;
		std::cout << "vec.rbegin()[10]:\t" << vec.rbegin()[10] << std::endl;
	}
	TESTHEAD;
	{
		std::cout << COLOR_YELLOW << COLOR_FAINT << "bidirectional iterator demonstrated on a map" << END << std::endl;
		ft::map<int, const char> map;
		for (unsigned int i = 0; i < 50; ++i)
			map.insert(ft::pair<int, const char>(i, 'a' + i));
		ft::map<int, const char>::iterator It(map.begin());
		ft::map<int, const char>::iterator ItE = map.end();
		ft::map<int, const char>::reverse_iterator ItR = map.rbegin();
		ft::map<int, const char>::reverse_iterator ItRE = map.rend();
		std::cout << COLOR_YELLOW << COLOR_FAINT << "end and rend should point to garbage values since they point to values after end/before begin" << END << std::endl;
		std::cout << "It:\t" << (*It).first << "\tItE:\t" << (*ItE).first << std::endl;
		std::cout << "ItR:\t" << (*ItR).first << "\tItRE:\t" << (*ItRE).first << std::endl;
		// std::cout << COLOR_YELLOW << COLOR_FAINT << "thus, if you take the value just before those, they should be begin and end, respectively" << END << std::endl;
		// std::cout << "It:\t" << *It.first << "\tItE:\t" << *(ItE - 1).first << std::endl;
		// std::cout << "ItR:\t" << *ItR.first << "\tItRE:\t" << *(ItRE - 1).first << std::endl;
		std::cout << "It  == ItRE: " << ((It == ItRE.base()) ? "true" : "false") << std::endl;
		std::cout << "ItR == ItE:  " << ((ItR.base() == ItE) ? "true" : "false") << std::endl;
		std::cout << COLOR_YELLOW << COLOR_FAINT << "Now we increase It and ItR by 3 and decrement ItE and ItRE by the same amount" << END << std::endl;
		++It;
		++It;
		++It;
		--ItE;
		--ItE;
		--ItE;
		++ItR;
		++ItR;
		++ItR;
		--ItRE;
		--ItRE;
		--ItRE;
		std::cout << "It:\t" << (*It).first << "\tItE:\t" << (*ItE).first << std::endl;
		std::cout << "ItR:\t" << (*ItR).first << "\tItRE:\t" << (*ItRE).first << std::endl;
	}
	TESTHEAD;
	TESTHEAD;

}
