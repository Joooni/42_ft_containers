/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:29:59 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/09 13:39:46 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include "ft_random_access_iterator.hpp"
#include <memory> // for std::allocator
#include <vector> // for looking up stuff
#include "utils.hpp"
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


		//-*-*-*-*-*-*-*-*-*-//
		//    Constructors   //
		//    Destructors    //
		//-*-*-*-*-*-*-*-*-*-//

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
	vector( InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value>::type* = 0) : _allocator(alloc)
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

	~vector()
	{
		this->clear();
		this->_allocator.deallocate(this->_start, this->_capacity);
	}

		//-*-*-*-*-*-*-*-*-*-//
		//    Assignments    //
		//-*-*-*-*-*-*-*-*-*-//

	vector &operator=(const vector &other)
	{
		if (*this == other)
			return (*this);
		this->clear();
		this->insert(this->_end, other.begin(), other.end());
		return (*this);
	}

	void assign(size_type count, const value_type &value)
	{
		this->clear();
		this->insert(this->_end, count, value);
	}

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		this->clear();
		this->insert(this->_end, first, last);
	}

	allocator_type get_allocator() const
	{
		return (this->_allocator);
	}

		//-*-*-*-*-*-*-*-*-*-//
		//   Element access  //
		//-*-*-*-*-*-*-*-*-*-//

	reference at(size_type pos)
	{
		if (pos >= this->size())
			throw std::out_of_range("Index out of range");
		return (*(this->_start + pos));
	}

	const_reference at(size_type pos) const
	{
		if (pos >= this->size())
			throw std::out_of_range("Index out of range");
		return (*(this->_start + pos));
	}

	reference operator[](size_type pos)
	{
		return (*(this->_start + pos));
	}

	const_reference operator[](size_type pos) const
	{
		return (*(this->_start + pos));
	}

	reference front()
	{
		return (*(this->_start));
	}

	const_reference front() const
	{
		return (*(this->_start));
	}

	reference back()
	{
		return (*(this->_end - 1));
	}

	const_reference back() const
	{
		return (*(this->_end - 1));
	}

	value_type *data()
	{
		return (this->_start);
	}

	const value_type *data() const
	{
		return (this->_start);
	}

		//-*-*-*-*-*-*-*-*-*-//
		//     Iterators     //
		//-*-*-*-*-*-*-*-*-*-//

	iterator begin()
	{
		iterator tmp(this->_start);
		return (tmp);
	}

	const_iterator begin() const
	{
		const_iterator tmp(this->_start);
		return (tmp);
	}

	iterator end()
	{
		iterator tmp(this->_end);
		return (tmp);
	}

	const_iterator end() const
	{
		const_iterator tmp(this->_end);
		return (tmp);
	}

	reverse_iterator rbegin()
	{
		reverse_iterator tmp(this->_end);
		return (tmp);
	}

	const_reverse_iterator rbegin() const
	{
		const_reverse_iterator tmp(this->_end);
		return (tmp);
	}

	reverse_iterator rend()
	{
		reverse_iterator tmp(this->_start);
		return (tmp);
	}

	const_reverse_iterator rend() const
	{
		const_reverse_iterator tmp(this->_start);
		return (tmp);
	}

	//-*-*-*-*-*-*-*-*-*-//
	//      Capacity     //
	//-*-*-*-*-*-*-*-*-*-//

	bool empty() const
	{
		if (this->size() == 0)
			return (true);
		return (false);
	}

	size_type size() const
	{
		return (this->_end - this->_start);
	}

	size_type max_size() const
	{
		return (this->_allocator.max_size());
	}

	void	reserve(size_type newCapacity)
	{
		if (newCapacity > this->max_size())
			throw std::length_error("HERE GOES ERROR CODE");
		if (newCapacity > this->_capacity)
		{
			pointer	first = this->_start;
			pointer	last = this->_end;
			this->_allocator.allocate(newCapacity);

			// // other implementation
			// size_type size = this->size();
			// pointer	temp = this->_start;
			// for (size_type i = 0; i < size; i++)
			// {
			// 	this->_allocator.construct(temp + i, *(first + i));
			// 	this->_allocator.destroy(first + i);
			// }
			this->_end = this->_start;
			while (first != last)
			{
				this->_allocator.construct(this->_end++, *first);
				this->_allocator.destroy(first);
				++first;
			}
			this->_allocator.deallocate(first - this->size(), this->_capacity);
			this->_capacity = newCapacity;
		}
	}

	unsigned int	capacity() const
	{
		return (this->_capacity);
	}
		//-*-*-*-*-*-*-*-*-*-//
		//     Modifiers     //
		//-*-*-*-*-*-*-*-*-*-//

	void clear()
	{
		for (size_type i = 0; i < size(); i++)
			this->_allocator.destroy(this->_start + i);
		this->_end = this->_start;
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
		ft::vector<T> filled(n, value);
		this->insert(position, filled.begin(), filled.end());
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
	{
		// find length of range to insert
		InputIterator	countIt = first;
		size_type		distance = 0;
		pointer			newStart = NULL;
		pointer			newEnd = NULL;
		pointer			copy = NULL;
		while (countIt++ != last)
			distance++;
		if (this->size() + distance > this->_capacity)
		{
			// reallocation necessary as new vector is bigger than current capacity
			size_type	newCapacity = 0;
			if (this->_capacity * 2 >= this->size() + distance)
				newCapacity = this->_capacity * 2;
			else
				newCapacity = this->size() + distance;
			// allocate necessary space and copy elements over one by one
			newStart = this->_allocator.allocate(newCapacity);
			copy = this->_start;
			newEnd = newStart;
			// first loop: copy everythig from the old vector over to the new one
			while (newEnd != position.base())
			{
				this->_allocator.construct(newEnd, *copy);
				this->_allocator.destroy(copy);
				++copy;
				++newEnd;
			}
			// second loop: construct new elements from the range [first, last)
			// could i use first as an iterator?
			while (first != last)
			{
				this->_allocator.construct(newEnd, *first);
				++newEnd;
				++first;
			}
			while (copy != this->_end)
			{
				this->_allocator.construct(newEnd, *copy);
				this->_allocator.destroy(copy);
				++copy;
				++newEnd;
			}
			this->_allocator.deallocate(this->_start, this->_capacity);
			this->_start = newStart;
			this->_end = newEnd;
			this->_capacity = newCapacity;
		}
		else
		{
			size_type distancePos = this->end() - position;	// distance to the value pointed to by position
			copy = this->_end - distancePos;				// start point of insertion of values
			if (this->_start != this->_end)
			{
				// vector is not empty, so move the values at position back by distance
				// to make space for the inserted values
				// start from the back to avoid complicated temporary storage
				for (pointer ptr = this->_end + distance - 1; ptr > this->_end + distance - distancePos - 1; ptr--)
				{
					this->_allocator.construct(ptr, *(ptr - distance));
					this->_allocator.destroy(ptr - distance);
				}
			}
			for (size_type i = 0; i < distance; i++)
				this->_allocator.construct(copy++, *(first++)); // put whatever first points to at copy and then increase both
			this->_end += distance;
		}
	}

	iterator erase(iterator pos)
	{
		return (this->_erase(pos, pos + 1));
	}

	iterator erase(iterator first, iterator last)
	{
		// how to invalidate iterators and references at and past erasure point?
		difference_type distance = last - first;

	}

	// void push_back(const value_type &value)
	// {

	// }

	// void pop_back()
	// {

	// }

	void resize(size_type count, value_type value = value_type())
	{
		if (count > this->max_size())
			throw std::length_error("HERE BE ERRORS");
		if (count > this->_capacity)
		{
			if (count > this->_capacity * 2)
				this->reserve(count);
			else
				this->reserve(this->_capacity * 2);
		}
		if (this->size() < count)
			for (size_type i = this->size(); i < count; i++)
				this->_allocator.construct(this->_end++, value);
		else if (this->size() > count)
			for (size_type i = this->size(); i > count; i--)
				this->_allocator.destroy((this->_end--) - 1);
	}

	private:
		pointer			_start;
		pointer			_end;
		unsigned int	_capacity;
		allocator_type	_allocator;
};

} // from namespace

#endif
