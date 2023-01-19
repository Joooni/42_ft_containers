/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:15:39 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/19 11:44:50 by jsubel           ###   ########.fr       */
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
	static const T value = val;
	typedef T value_type;
	typedef integral_constant<T, val> type;
	operator value_type() {return (this->value);}
};

template <class T1, class T2>
class pair
{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair(): first(), second() {};
		template <class P1, class P2>
		pair(const pair <P1, P2> &pair): first(pair.first), second(pair.second) {};
		pair(const first_type &first, const second_type &second): first(first), second(second) {};
		pair &operator=(const pair &rhs)
		{
			this->first = rhs.first;
			this->second = rhs.second;
			return (*this);
		}
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

/*
Two ranges are considered equal if they have the same number of elements and,
for every iterator i in the range [first1,last1), *i equals *(first2 + (i - first1))
*/

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
		if (!p(*first1, *first2))
			return (false);
	}
	return (true);
}
/*
Lexicographical comparison is an operation with the following properties:
 * Two ranges are compared element by element.
 * The first mismatching element defines which range is lexicographically less or greater than the other.
 * If one range is a prefix of another, the shorter range is lexicographically less than the other.
 * If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
 * An empty range is lexicographically less than any non-empty range.
 * Two empty ranges are lexicographically equal.
*/
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	return((first1 == last1) && (first2 != last2));
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}

template <class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y)
{
	return (pair<T1,T2>(x,y));
}

template<typename T>
T get_key(T *key)
{
	return (*key);
}

template<typename key, typename value>
key get_key(ft::pair<key, value> *pair)
{
	return (pair->first);
}
/*
	here goes
	pair
	make_pair
*/

} // ft namespace

#endif
