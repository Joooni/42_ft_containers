/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:29:59 by jsubel            #+#    #+#             */
/*   Updated: 2022/12/14 10:54:03 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECOTR_HPP

#include <iostream>

namespace ft
{
template <typename T>
class Vector
{
	public:
		Vector();
		Vector(const Vector &rhs);
		Vector &operator=(const Vector &rhs);
		~Vector();

		bool	empty();
		int		size();
		int		capacity();

		bool operator==(const Vector &rhs) const;

	private:
		unsigned int	_capacity;
		unsigned int	_size;
		pointer			_start;
		pointer			_end;
}
} // from namespace

#include "Vector.tpp"

#endif
