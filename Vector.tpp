/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:47:13 by jsubel            #+#    #+#             */
/*   Updated: 2022/12/14 11:57:44 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Vector::Vector(): _capacity(1), _size(0) /*_start(), _end() */ {}

Vector::Vector(const Vector &rhs)
{
	*this = rhs;
}

Vector::~Vector() {}

bool	Vector::empty()
{
	return (size == 0);
}

int		Vector::size()
{
	return (this->_size);
}

int		Vector::capacity()
{
	return (this->_capacity);
}

bool	Vector::operator==(const Vector &rhs) const
{
	if (this->_size != rhs.size())
		return false;
	for (unsigned int i = 0; i < this->_size; i++)
	{

	}
}

Vector &Vector::operator=(const Vector &rhs)
{
	this->_capacity = rhs.capacity();
	this->_size = rhs.size();
	for (unsigned int i; i < rhs.size(); i++)
		this->array[i] = rhs.array[i];
	return (*this);
}

std::ostream &operator<<(std::ostream &os, const Vector &v)
{
	for (unsigned int i = 0; i < v.size(); i++)
		os << v.array[i] << " ";
	os << " || ";
	for (unsigned int i = v.size(); i < v.capacity(); i++)
		os << v.array[i] << " ";
	os << std::endl;
	return (os);
}