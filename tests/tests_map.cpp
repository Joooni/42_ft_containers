/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:16:57 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/16 10:29:51 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <functional>
#include <time.h>
#include <list>
#include <stdlib.h>
#include "../vector.hpp"
#include "test_utils.hpp"

int main(void)
{
	int nbr_tests = 1;
	{
		TESTHEAD(nbr_tests++);
		std::list< ft::pair<int, int> > lst;
		unsigned int lst_size = 26;
		for (unsigned int i = 0; i < lst_size; ++i)
			lst.push_back(ft::pair<int, int>(lst_size - i, i));

		ft::map<int, int> mp(lst.begin(), lst.end());
		// mp.printTree();
		// mp.clear();
		// std::cout << "cleared tree" << std::endl;
		// mp.printTree();
	}
	// {
	// 	std::list<int, int> lst;
	// 	unsigned int lst_size = 10;
	// 	for (unsigned int i = 0; i < lst_size; ++i)
	// 	{
	// 		lst.push_back(T3(lst_size - i, i));
	// 		std::cout << "key: " << lst_size - i << "\tval: " << i << std::endl;
	// 	}
	// 	std::cout << "before range construction" << std::endl;
	// 	ft::map<int, int> mp(lst.begin(), lst.end());
	// 	std::cout << "after range construction" << std::endl;
	// 	ft::map<int, int>::iterator it = mp.begin(), ite = mp.end();
	// 	std::cout << "after iterator creation" << std::endl;
	// 	mp.printTree();
	// }
}
