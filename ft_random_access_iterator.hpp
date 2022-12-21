/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:18:31 by jsubel            #+#    #+#             */
/*   Updated: 2022/12/21 15:49:05 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOPR
# define FT_RANDOM_ACCESS_ITERATOPR

# include "ft_iterator.hpp"
// to look up actual iterator implementation lol
# include <iterator>
namespace ft
{
template<typename T>
class random_access_iterator : public iterator<random_access_iterator_tag, T>
{
	private:
		pointer	_current;

	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		// Constructors
		random_access_iterator() : _current(0) {}
		random_access_iterator(const random_access_iterator &rhs) : _current(rhs._current) {}
		random_access_iterator(pointer ptr) : _current(ptr) {}

		pointer	base() const
		{
			return (this->_current);
		}

		//-*-*-*-*-*-*-*-*-*-//
		// operator overloads//
		//-*-*-*-*-*-*-*-*-*-//

		// arithmetic operators

		random_access_iterator &operator=(const random_access_iterator<T> &rhs)
		{
			this->_current = rhs._current;
			return (*this);
		}

		random_access_iterator &operator++()
		{
			this->_current;
			return (*this);
		}

		random_access_iterator &operator++(int)
		{
			random_access_iterator tmp(*this);
			this->_current++;
			//this out ++this->current
			return (tmp);
		}

		random_access_iterator &operator--()
		{
			this->_current--;
			return (*this);
		}

		random_access_iterator &operator+(difference_type n) const
		{
			this->_current += n;
			return (*this);
		}

		random_access_iterator &operator-(difference_type n) const
		{
			this->_current -= n;
			return (*this);
		}

		//comparsion overloads
		//non constant iterators
		bool operator==(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current != rhs.base());
		}

		bool operator>(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current > rhs.base());
		}

		bool operator<(const random_access_iterator<T> &rhs) const;
		{
			return (this->_current < rhs.base());
		}
};

template<typename T>
class constant_random_access_iterator : public iterator<random_access_iterator_tag, T>
{
	private:
		pointer	_current;

	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef const typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		// Constructors
		constant_random_access_iterator() : _current(0) {}
		template <typename T2>
		constant_random_access_iterator(const random_access_iterator<T2> &rhs) : _current(rhs.base()) {}
		constant_random_access_iterator(const constant_random_access_iterator &rhs) : _current(rhs.base()) {}
		constant_random_access_iterator(pointer ptr) : _current(ptr) {}

		pointer	base() const
		{
			return (this->_current);
		}

		//-*-*-*-*-*-*-*-*-*-//
		// operator overloads//
		//-*-*-*-*-*-*-*-*-*-//

		// arithmetic operators

		constant_random_access_iterator &operator=(const constant_random_access_iterator<T> &rhs)
		{
			this->_current = rhs._current;
			return (*this);
		}

		constant_random_access_iterator &operator++()
		{
			this->_current++;
			return (*this);
		}

		constant_random_access_iterator &operator--()
		{
			this->_current--;
			return (*this);
		}

		constant_random_access_iterator &operator+(difference_type n) const
		{
			this->_current += n;
			return (*this);
		}

		constant_random_access_iterator &operator-(difference_type n) const
		{
			this->_current -= n;
			return (*this);
		}

		//comparsion overloads
		//non constant iterators
		bool operator==(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current != rhs.base());
		}

		bool operator>(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current > rhs.base());
		}

		bool operator<(const constant_random_access_iterator<T> &rhs) const;
		{
			return (this->_current < rhs.base());
		}
}

} //namespace

#endif
