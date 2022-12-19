/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:18:31 by jsubel            #+#    #+#             */
/*   Updated: 2022/12/19 16:45:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOPR
# define FT_RANDOM_ACCESS_ITERATOPR

# include "ft_iterator.hpp"
// to look up actual iterator implementation lol
// # include <iterator>
namespace ft
{
template<typename T>
class random_access_iterator : public iterator<random_access_iterator_tag, T>
{
	private:
		pointer	_curr;

	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		// Constructors
		random_access_iterator() : _curr(0) {}
		random_access_iterator(const random_access_iterator &rhs) : _curr(rhs._curr) {}
		random_access_iterator(pointer ptr) : _curr(ptr) {}

		//-*-*-*-*-*-*-*-*-*-//
		// operator overloads//
		//-*-*-*-*-*-*-*-*-*-//

		random_access_iterator &operator=(const random_access_iterator<T> &rhs)
		{
			this->_curr = rhs._curr;
			return (*this);
		}

		random_access_iterator &operator++()
		{
			this->_curr++;
			return (*this);
		}

		random_access_iterator &operator--()
		{
			this->_curr--;
			return (*this);
		}

		random_access_iterator &operator+(difference_type n) const
		{
			this->_curr += n;
			return (*this);
		}

		random_access_iterator &operator-(difference_type n) const
		{
			this->_curr -= n;
			return (*this);
		}

		//comparsion overloads
		//non constant iterators
		bool operator==(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr == rhs._curr);
		}

		bool operator>=(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr >= rhs._curr);
		}

		bool operator<=(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr <= rhs._curr);
		}

		bool operator!=(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr != rhs._curr);
		}

		bool operator>(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr > rhs._curr);
		}

		bool operator<(random_access_iterator<T> &rhs) const;
		{
			return (this->_curr < rhs._curr);
		}





}

} //namespace

#endif
