/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:15:39 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/10 18:16:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <type_traits> // for is_integral

#ifndef UTILITY_HPP
# define  UTILITY_HPP
namespace ft
{
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type;};

template <class T, T val>
class integral_constant {
public:
	const T value = val;
	typedef T value_type;
	typedef integral_constant<T, val> type;
	operator value_type() {return (this->value);}
};

typedef	integral_constant <bool, true>	true_type;
typedef	integral_constant <bool, false>	false_type;

template <class T>
struct	is_integral : public false_type {};

template <> struct			is_integral<bool> :						public true_type {};
template <> struct			is_integral<char> :						public true_type {};
template <> struct			is_integral<char16_t> :					public true_type {};
template <> struct			is_integral<char32_t> :					public true_type {};
template <> struct			is_integral<wchar_t> :					public true_type {};
template <> struct			is_integral<signed char> :				public true_type {};
template <> struct			is_integral<short int> :				public true_type {};
template <> struct			is_integral<int> :						public true_type {};
template <> struct			is_integral<long int> :					public true_type {};
template <> struct			is_integral<long long int> :			public true_type {};
template <> struct			is_integral<unsigned char> :			public true_type {};
template <> struct			is_integral<unsigned short int> :		public true_type {};
template <> struct			is_integral<unsigned int> :				public true_type {};
template <> struct			is_integral<unsigned long int> :		public true_type {};
template <> struct			is_integral<unsigned long long int> :	public true_type {};

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(*first1 == *first2))
			return (false);
	}
	return (true);
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!p(*first1, *first2)
			return (false);
	}
	return (true);	
}
/*
	here goes
	equal
	lexicographical_compare
	pair
	make_pair
*/

} // ft namespace

#endif
