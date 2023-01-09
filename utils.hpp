/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:15:39 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/09 13:41:55 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef UTILITY_HPP
# define  UTILITY_HPP
namespace ft
{
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type;};

/*
	here goes
	is_integral
	equal
	lexicographical_compare
	pair
	make_pair
*/

} // ft namespace

#endif
