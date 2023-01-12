/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:15:34 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/12 11:09:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

# include <memory>
# include <iostream>

namespace ft
{
template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

/**
 *  @defgroup iterator_tags Iterator Tags
 *  These are empty types, used to distinguish different iterators.  The
 *  distinction is not made by what they contain, but simply by what they
 *  are.  Different underlying algorithms can then be used based on the
 *  different operations supported by different iterator types.
 */
struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};


template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};
template <class T>
struct iterator_traits<const T*>
{
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

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
		// Constructors
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
bool operator== (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class itLeft, class itRight>
bool operator== (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class itLeft, class itRight>
bool operator!= (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator< (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class itLeft, class itRight>
bool operator< (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class itLeft, class itRight>
bool operator<= (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator> (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class itLeft, class itRight>
bool operator> (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class itLeft, class itRight>
bool operator>= (const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return (rev_it + n);
}

template <typename itLeft, typename itRight>
typename reverse_iterator<itLeft>::difference_type operator-(const reverse_iterator<itLeft> &lhs, const reverse_iterator<itRight> &rhs)
{
	return (rhs.base() - lhs.base());
}
} // namespace

#endif
