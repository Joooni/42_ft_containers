/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:29:59 by jsubel            #+#    #+#             */
/*   Updated: 2022/12/19 10:51:59 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECOTR_HPP

#include <iostream>

namespace ft
{
template < typename T, typename Alloc = std::allocator<T> >
class Vector
{
	public:

		typedef	/*here goes something*/ iterator;
		typedef	/*here goes something*/ const_iterator;

		Vector();
		Vector(const Vector &rhs);
		Vector &operator=(const Vector &rhs);
		~Vector();

		bool	empty();
		int		size();
		int		capacity();

		bool operator==(const Vector &rhs) const;

		friend std::ostream &operator<<(std::ostream &os, const Vector &v);

	private:
		unsigned int	_capacity;
		unsigned int	_size;
		pointer			_start;
		pointer			_end;
}
} // from namespace

#include "Vector.tpp"

#endif
