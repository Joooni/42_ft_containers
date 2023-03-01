/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:19:49 by jsubel            #+#    #+#             */
/*   Updated: 2023/03/01 08:42:12 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

#include "ft_iterator.hpp"

namespace ft
{

template <class Iterator>
class reverse_iterator
{
	public:
		typedef Iterator	iterator_type;

		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	private:
		iterator_type _current;

	public:

		//-*-*-*-*-*-*-*-*-*-//
		//    Constructors   //
		//    Destructors    //
		//-*-*-*-*-*-*-*-*-*-//

		reverse_iterator(): _current() {}
		explicit reverse_iterator(iterator_type it): _current(it) {}
		template <class T>
		reverse_iterator(const reverse_iterator<T> &revIt): _current(revIt.base()) {}

		iterator_type base() const
		{
			return (this->_current);
		}

		//-*-*-*-*-*-*-*-*-*-//
		// operator overloads//
		//-*-*-*-*-*-*-*-*-*-//

		// arithmetic operators

		reverse_iterator &operator=(const reverse_iterator &rhs)
		{
			this->_current = rhs.base();
			return (*this);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->_current - n));
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->_current + n));
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->_current -= n;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_current += n;
			return (*this);
		}

		reverse_iterator &operator++()
		{
			this->_current--;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator &operator--()
		{
			this->_current++;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		reference operator*() const
		{
			iterator_type _temp(this->_current);
			--_temp;
			return (*_temp);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reference	operator[](difference_type n) const
		{
			return (this->base()[-n - 1]);
		}
};

// comparsion overloads

template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class itLeft, class itRight>
bool operator==(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class itLeft, class itRight>
bool operator!=(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class itLeft, class itRight>
bool operator<(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class itLeft, class itRight>
bool operator<=(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class itLeft, class itRight>
bool operator>(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class itLeft, class itRight>
bool operator>=(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return (rev_it + n);
}

template <typename itLeft, typename itRight>
typename reverse_iterator<itLeft>::difference_type operator-(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (rhs.base() - lhs.base());
}

} // ft namespace

#endif
