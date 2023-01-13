/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:12:40 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/13 13:26:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "RBT.hpp"
#include "ft_iterator.hpp"
#include <map>

namespace ft
{
template <typename T, class Tree>
class const_RBT_iterator;


template<typename T, typename Tree>
class RBT_iterator: public iterator<bidirectional_iterator_tag, T>
{
	public:
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef typename Tree::value_type 															value_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::pointer				pointer;

	private:
		T *_current;
		T *_end;
		T *_rend;

	public:

		//-*-*-*-*-*-*-*-*-*-//
		//    Constructors   //
		//    Destructors    //
		//-*-*-*-*-*-*-*-*-*-//

		RBT_iterator(): _current(0), _end(0), _rend(0) {}
		RBT_iterator(T *curr, T *end, T *rend):  _current(curr), _end(end), _rend(rend) {}
		RBT_iterator(const RBT_iterator &rhs): _current(rhs._current), _end(rhs._end), _rend(rhs._current) {}
		template <typename differentTree>
		RBT_iterator(const RBT_HPP<T, differentTree> &rhs):  _current(rhs.base()), _end(rhs.getEnd()), _rend(rhs.getRend()) {}


		RBT_iterator &operator=(const RBT_iterator &rhs)
		{
			this->_current = rhs._current;
			this->_end = rhs._end;
			this->_rend = rhs._rend;
			return (*this);
		}

		T *base() const
		{
			return (this->_current);
		}

		//-*-*-*-*-*-*-*-*-*-//
		//     Operators     //
		//-*-*-*-*-*-*-*-*-*-//


		RBT_iterator &operator++()
		{

		}

		RBT_iterator operator++(int)
		{
			RBT_iterator temp = *this;
			++(*this);
			return (temp);
		}

		RBT_iterator &operator--()
		{

		}

		RBT_iteraotr operator--(int)
		{
			RBT_iterator temp = *this;
			--(*this);
			return (temp);
		}

		bool operator==(RBT_iterator<T, Tree> rhs)
		{
			return (this->base() == rhs.base());
		}

		bool operator!=(RBT_iterator<T, Tree> rhs) const
		{
			return (this->base() != rhs.base());
		}

		T *getEnd() const
		{
			return (this->_end);
		}

		T *getRend() const
		{
			return (this->_rend);
		}

		//-*-*-*-*-*-*-*-*-*-//
		//  pointer and ref  //
		//-*-*-*-*-*-*-*-*-*-//

		reference operator*() const
		{
			return (*(this->_current)->content);
		}

		pointer operator->() const
		{
			return (this->_current->content);
		}



}

} // namespace ft

#endif