/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:39:36 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/07 17:51:15 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include "RBT.hpp"
#include "RBT_iterator.hpp"
#include "utils.hpp"
#include <memory>

// checking out STL
// #include <bits/stl_tree.h>
// #include <bits/stl_map.h> 

namespace ft
{

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map
{
	public:
		typedef Key	 				key_type;
		typedef T	 				mapped_type;
		typedef pair<const Key, T>	value_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Compare				key_compare;
		typedef Alloc				allocator_type;

		typedef typename allocator_type::reference		 reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer		 pointer;
		typedef typename allocator_type::const_pointer	 const_pointer;
		
		typedef RBT<value_type, key_compare, allocator_type>	tree_type;
		
		typedef typename ft::RBT_iterator<typename tree_type::node, tree_type>		 iterator;
		typedef typename ft::const_RBT_iterator<typename tree_type::node, tree_type> const_iterator;
		typedef typename ft::reverse_iterator<iterator>								 reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						 const_reverse_iterator;
	
	private:

		ft::RBT<value_type, key_compare, allocator_type>	_tree;
		key_compare											_compare;
		allocator_type										_allocator;

	public:
		// std::map::value_compare is a function object that compares objects of type map::value_type (key-value pairs)
		// by comparing of the first components of the pairs. 
		// https://en.cppreference.com/w/cpp/container/map/value_compare for details
		class value_compare : std::binary_function<value_type, value_type, bool>
		{
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool operator()( const value_type& lhs, const value_type& rhs ) const
				{
					return (comp(lhs.first, rhs.first));
				}
		};
	
		//-*-*-*-*-*-*-*-*-*-//
		//    Constructors   //
		//    Destructors    //
		//-*-*-*-*-*-*-*-*-*-//
	
		explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc), _comp(comp), _allocator(alloc)	
		{
			
		}
		
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp), _allocator(alloc)
		{
			this->insert(first, last);
		}

		map (const map &other)
		{
			*this = other;
		}
		
		~map()
		{
			this->_tree.clear();
		
		//-*-*-*-*-*-*-*-*-*-//
		}
		//    Assignments    //
		//-*-*-*-*-*-*-*-*-*-//

		map &operator=(const map &rhs)
		{
			this->_allocator = rhs._allocator;
			this->_compare = rhs._compare;
			this->clear();
			this->_tree = rhs._tree;
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		//-*-*-*-*-*-*-*-*-*-//
		//   Element access  //
		//-*-*-*-*-*-*-*-*-*-//

		mapped_type &at(const key_type &key)
		{
			iterator valIter = find(key);
			if (valIter == this->end())
				throw (std::out_of_range("index out of range"));
			return ((*valIter).second);
		}
		const mapped_type &at(const key_type &key) const
		{
			const_iterator valIter = find(key);
			if (valIter == this->end())
				throw (std::out_of_range("index out of range"));
			return ((*valIter).second);
		}

		mapped_type &operator[](const key_type &key)
		{
			// call insert here
		}

		//-*-*-*-*-*-*-*-*-*-//
		//     Iterators     //
		//-*-*-*-*-*-*-*-*-*-//

		iterator begin()
		{
			return (this->_tree.begin());
		}

		const_iterator begin() const
		{
			return (this->_tree.begin());
		}

		iterator end()
		{
			return (this->_tree.end());
		}
		
		const_iterator end() const
		{
			return (this->_tree.end());
		}

		reverse_iterator rbegin()
		{
			reverse_iterator rIter(this->end());
			return (rIter)
		}

		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator rIter(this->end());
			return (rIter)
		}

		reverse_iterator rend()
		{
			reverse_iterator rIter(this->begin());
			return (rIter);
		}
		
		const_reverse_iterator rend() const
		{
			const_reverse_iterator rIter(this->begin());
			return (rIter);
		}

		//-*-*-*-*-*-*-*-*-*-//
		//      Capacity     //
		//-*-*-*-*-*-*-*-*-*-//

		bool empty() const
		{
			return (!this.size());
		}
		
		size_type size() const
		{
			return (this->_tree.size());
		}

		size_type max_size() const
		{
			return (this->_tree.max_size());
		}



}

} // namespace ft

#endif
