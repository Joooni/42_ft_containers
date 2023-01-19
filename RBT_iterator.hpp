/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:12:40 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/19 11:21:10 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "RBT.hpp"
#include "ft_reverse_iterator.hpp"
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
		RBT_iterator(const RBT_iterator<T, differentTree> &rhs):  _current(rhs.base()), _end(rhs.getEnd()), _rend(rhs.getRend()) {}


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
			T *temp = this->_current;

			// if current points to reverse end, go to its parent (e.g. min)
			if (temp == this->_rend)
				temp = this->_rend->parent;
			// see if there exists a right subtree
			// if so, find minimum of that
			// otherwise, go to first right parent
			else if (temp->right_child)
			{
				temp = temp->right_child;
				while (temp->left_child)
					temp = temp->left_child;
			}
			else
			{
				while (temp->parent && temp == temp->parent->right_child) //parent->right_child means its a left parent
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;	// set temp to the according node
				else						// if no parent exists, root was hit; that means we were at the rightmost node and thus at max
					temp = this->_end;
			}
			this->_current = temp;
			return (*this);
		}

		RBT_iterator operator++(int)
		{
			RBT_iterator temp = *this;
			++(*this);
			return (temp);
		}

		// same logic as in increment operator, just the other way around
		RBT_iterator &operator--()
		{
			T *temp = this->_current;

			if (temp == this->_end)
				temp = this->_end->parent;
			else if (temp->left_child)
			{
				temp = temp->left_child;
				while (temp->right_child)
					temp = temp->right_child;
			}
			else
			{
				while (temp->parent && temp = temp->parent->right_child)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else
					temp = this->_rend;
			}
			this->_current = temp;
			return (*this);
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

template<typename T, typename Tree>
class const_RBT_iterator: public iterator<bidirectional_iterator_tag, T>
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

		const_RBT_iterator(): _current(0), _end(0), _rend(0) {}
		const_RBT_iterator(T *curr, T *end, T *rend):  _current(curr), _end(end), _rend(rend) {}
		const_RBT_iterator(const const_RBT_iterator &rhs): _current(rhs._current), _end(rhs._end), _rend(rhs._current) {}
		const_RBT_iterator(const RBT_iterator<T, Tree> &rhs) { *this = rhs;}
		template <typename differentTree>
		const_RBT_iterator(const RBT_iterator<T, differentTree> &rhs):  _current(rhs.base()), _end(rhs.getEnd()), _rend(rhs.getRend()) {}
		template <typename differentTree>
		const_RBT_iterator(const const_RBT_iterator<T, differentTree> &rhs):  _current(rhs.base()), _end(rhs.getEnd()), _rend(rhs.getRend()) {}

		const_RBT_iterator &operator=(const const_RBT_iterator &rhs)
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


		const_RBT_iterator &operator++()
		{
			T *temp = this->_current;

			// if current points to reverse end, go to its parent (e.g. min)
			if (temp == this->_rend)
				temp = this->_rend->parent;
			// see if there exists a right subtree
			// if so, find minimum of that
			// otherwise, go to first right parent
			else if (temp->right_child)
			{
				temp = temp->right_child;
				while (temp->left_child)
					temp = temp->left_child;
			}
			else
			{
				while (temp->parent && temp == temp->parent->right_child) //parent->right_child means its a left parent
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;	// set temp to the according node
				else						// if no parent exists, root was hit; that means we were at the rightmost node and thus at max
					temp = this->_end;
			}
			this->_current = temp;
			return (*this);
		}

		const_RBT_iterator operator++(int)
		{
			const_RBT_iterator temp = *this;
			++(*this);
			return (temp);
		}

		// same logic as in increment operator, just the other way around
		const_RBT_iterator &operator--()
		{
			T *temp = this->_current;

			if (temp == this->_end)
				temp = this->_end->parent;
			else if (temp->left_child)
			{
				temp = temp->left_child;
				while (temp->right_child)
					temp = temp->right_child;
			}
			else
			{
				while (temp->parent && temp = temp->parent->right_child)
					temp = temp->parent;
				if (temp->parent)
					temp = temp->parent;
				else
					temp = this->_rend;
			}
			this->_current = temp;
			return (*this);
		}

		RBT_iteraotr operator--(int)
		{
			const_RBT_iterator temp = *this;
			--(*this);
			return (temp);
		}

		bool operator==(const_RBT_iterator<T, Tree> rhs)
		{
			return (this->base() == rhs.base());
		}

		bool operator!=(const_RBT_iterator<T, Tree> rhs) const
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