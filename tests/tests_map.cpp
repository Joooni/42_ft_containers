/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:16:57 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/15 09:16:58 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <functional>
#include <time.h>
#include <list>
#include <stdlib.h>
#include "../vector.hpp"

#define DELIM	std::string(10, '~')

int main(void)
{
	std::list< ft::pair<const char, int> > lst;
	unsigned int lst_size = 26;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const char, int>('a' + i, (i + 1) * 7));


	ft::map<char, int> mp(lst.begin(), lst.end());
	mp.printTree();
	mp.clear();
	std::cout << DELIM << "cleared tree" << DELIM << std::endl;
	mp.printTree();
	// mp.erase('h');
	// std::cout << DELIM << "Test 2" << DELIM << std::endl;
	// {
	// 	ft::RBT<int, std::less<int> >	RBTommy;
	// 	srand(time(NULL));
	// 	for (int i = 0; i < 20; i++)
	// 	{
	// 		int nbr = rand() % 47;
	// 		std::cout << nbr <<std::endl;
	// 		RBTommy.insert(nbr);
	// 	}
	// 	RBTommy.printTree();
	// }
}
