/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:32:51 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/14 10:30:54 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
#include <stack>
namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container	container_type;
			typedef T			value_type;
			typedef size_t		size_type;

			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;

			explicit stack(const container_type &container = container_type()): c(container) {}
			~stack() {}
			stack &operator=(const stack &rhs)
			{
				this->c = rhs.c;
				return (*this);
			}

			reference top()
			{
				return (this->c.back());
			}

			const_reference top() const
			{
				return (this->c.back());
			}

			bool empty() const
			{
				return (!this->c.size());
			}

			size_type size() const
			{
				return (this->c.size());
			}

			void push(const value_type &value)
			{
				this->c.push_back(value);
			}

			void pop()
			{
				this->c.pop_back();
			}

			template<typename A, typename B>
			friend bool operator==(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template<typename A, typename B>
			friend bool operator<(const stack<A, B> &lhs, const stack<A, B> &rhs);

		protected: //STL has this as protected, why?
			container_type c;

	}

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (!(lhs < rhs));
	}

} // ft namespace

#endif
