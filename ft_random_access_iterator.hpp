/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:18:31 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/13 12:12:29 by jsubel           ###   ########.fr       */
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
class constant_random_access_iterator;

template<typename T>
class random_access_iterator : public iterator<random_access_iterator_tag, T>
{

	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

	private:
		pointer	_current;

	public:
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
			this->_current++;
			return (*this);
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			this->_current++;
			return (tmp);
		}

		random_access_iterator &operator--()
		{
			this->_current--;
			return (*this);
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp(*this);
			this->_current--;
			return (tmp);
		}

		random_access_iterator operator+(difference_type n) const
		{
			return (this->_current + n);
		}

		random_access_iterator operator-(difference_type n) const
		{
			return (this->_current - n);
		}

		random_access_iterator &operator+=(difference_type n)
		{
			this->_current += n;
			return (*this);
		}

		random_access_iterator &operator-=(difference_type n)
		{
			this->_current -= n;
			return (*this);
		}

		//comparsion overloads
		//compare with non constant iterators
		bool operator==(random_access_iterator<T> rhs) const
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(random_access_iterator<T> rhs) const
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(random_access_iterator<T> rhs) const
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(random_access_iterator<T> rhs) const
		{
			return (this->_current != rhs.base());
		}

		bool operator>(random_access_iterator<T> rhs) const
		{
			return (this->_current > rhs.base());
		}

		bool operator<(random_access_iterator<T> rhs) const
		{
			return (this->_current < rhs.base());
		}

		//compare with constant iterators
		bool operator==(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current != rhs.base());
		}

		bool operator>(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current > rhs.base());
		}

		bool operator<(constant_random_access_iterator<const T> rhs) const
		{
			return (this->_current < rhs.base());
		}

		T &operator*() const
		{
			return (*(this->_current));
		}

		pointer operator->() const
		{
			return (this->_current);
		}

		reference operator[](difference_type n) const
		{
			return (*(this->_current + n));
		}
};

template<typename T>
class constant_random_access_iterator : public iterator<random_access_iterator_tag, T>
{

	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef const typename ft::iterator<random_access_iterator_tag, T>::value_type	value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

	private:
		pointer	_current;

	public:
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
			this->_current = rhs.base();
			return (*this);
		}

		constant_random_access_iterator &operator++()
		{
			this->_current++;
			return (*this);
		}

		constant_random_access_iterator operator++(int)
		{
			constant_random_access_iterator tmp(*this);
			this->_current++;
			return (tmp);
		}

		constant_random_access_iterator &operator--()
		{
			this->_current--;
			return (*this);
		}

		constant_random_access_iterator operator--(int)
		{
			constant_random_access_iterator tmp(*this);
			this->_current--;
			return (tmp);
		}

		constant_random_access_iterator operator+(difference_type n) const
		{
			return (this->_current + n);
		}

		constant_random_access_iterator operator-(difference_type n) const
		{
			return (this->_current - n);
		}

		constant_random_access_iterator &operator+=(difference_type n)
		{
			this->_current += n;
			return (*this);
		}

		constant_random_access_iterator &operator-=(difference_type n)
		{
			this->_current -= n;
			return (*this);
		}

		//comparsion overloads
		//compare with non constant iterators
		bool operator==(const random_access_iterator<T> rhs) const
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(const random_access_iterator<T> rhs) const
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(const random_access_iterator<T> rhs) const
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(const random_access_iterator<T> rhs) const
		{
			return (this->_current != rhs.base());
		}

		bool operator>(const random_access_iterator<T> rhs) const
		{
			return (this->_current > rhs.base());
		}

		bool operator<(const random_access_iterator<T> rhs) const
		{
			return (this->_current < rhs.base());
		}

		//compare with constant iterators
		bool operator==(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current == rhs.base());
		}

		bool operator>=(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current >= rhs.base());
		}

		bool operator<=(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current <= rhs.base());
		}

		bool operator!=(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current != rhs.base());
		}

		bool operator>(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current > rhs.base());
		}

		bool operator<(const constant_random_access_iterator<T> rhs) const
		{
			return (this->_current < rhs.base());
		}

		T &operator*() const
		{
			return (*(this->_current));
		}

		pointer operator->() const
		{
			return (this->_current);
		}

		reference operator[](difference_type n) const
		{
			return (*(this->_current + n));
		}
};

// non const
template<class T>
random_access_iterator<T> operator+(typename ft::iterator<random_access_iterator_tag, T>::difference_type n, random_access_iterator<T> &it)
{
	return (it.base() + n);
}

template<class T>
random_access_iterator<T> operator+(typename ft::iterator<random_access_iterator_tag, T>::difference_type n, constant_random_access_iterator<T> &it)
{
	return (it.base() + n);
}

template<class T>
typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return (lhs.base() - rhs.base());
}

template<class T>
typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const constant_random_access_iterator<const T> &rhs)
{
	return (lhs.base() - rhs.base());
}

template<class T>
typename random_access_iterator<T>::difference_type operator-(const constant_random_access_iterator<const T> &lhs, const random_access_iterator<T> &rhs)
{
	return (lhs.base() - rhs.base());
}

template<class T>
typename random_access_iterator<T>::difference_type operator-(const constant_random_access_iterator<T> &lhs, const constant_random_access_iterator<T> &rhs)
{
	return (lhs.base() - rhs.base());
}

} //namespace


#endif
