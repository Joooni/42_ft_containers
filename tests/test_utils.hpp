/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:01:31 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/16 10:16:58 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define TESTHEAD(NBR)		std::cout << COLOR_YELLOW << std::string(20, '~') << "Test " << NBR << std::string(20, '~') << END << std::endl;


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}
