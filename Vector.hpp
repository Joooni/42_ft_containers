/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:29:59 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/04 12:51:28 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include "ft_random_access_iterator.hpp"
#include <memory> // for std::allocator
#include <vector> // for looking up stuff

namespace ft
{
template < class T, class Allocator = std::allocator<T> >
class vector
{
	public:

	typedef	T			value_type;
	typedef	Allocator	allocator_type;

	typedef typename allocator_type::size_type				size_type;
	typedef typename allocator_type::difference_type		difference_type;

	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;

	typedef typename ft::random_access_iterator<value_type>				iterator;
	typedef typename ft::constant_random_access_iterator<value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	// construct empty vector
	explicit vector(const allocator_type &alloc = allocator_type()) : _start(0), _end(0), _capacity(0), _allocator(alloc) {}

	// construct vector of n elements with value
	explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type()) : _capacity(n), _allocator(alloc)
	{
		this->_start = this->_allocator.allocate(n);
		this->_end = this->_start;
		for (size_type i = 0; i < n; i++)
			this->_allocator.construct(this->_end++, value);
	}

	// constructs container with contents of range [first, last)
	template<class InputIterator>
	vector( InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _allocator(alloc)
	{
		InputIterator	countIt = first;
		size_type		count = 0;

		while (countIt++ != last)
			count++;
		this->_capacity = count;
		this->_start = this->_allocator.allocate(this->_capacity);
		this->_end = this->_start;
		while (first != last)
			this->_allocator.construct(this->_end++, *(first++));
	}

	// copy constructor
	vector(const vector &other) : _start(0), _end(0), _capacity(other.capacity())
	{
		this->_start = this->_allocator.allocate(this->_capacity);
		this->_end = this->_start;
		this->insert(this->_end, other.begin(), other.end());
	}

	// inserts
	// add one element
	iterator insert(iterator position, const value_type &value)
	{
		size_type distance = position - this->_begin;
		this->insert(position, 1, value);
		return (this->_begin() + distance);
	}

	// add n elements of value
	void insert(iterator position, size_type n, const value_type &value)
	{
		ft::vector<T> filledWithValue(n, value);
		this->insert(position, filledWithValue.begin(), filledWithValue.end());
	}

	template <class InputIterator>
	iterator insert(iterator position, InputIterator first, InputIterator last)
	{

	}

	unsigned int	capacity() const
	{
		return (this->_capacity);
	}

	allocator_type	allocator_type() const
	{
		return (this->_allocator);
	}

	private:
		pointer			_start;
		pointer			_end;
		unsigned int	_capacity;
		allocator_type	_allocator;
}
} // from namespace

#endif
