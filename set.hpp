/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:06:53 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/14 14:45:34 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP
#include "RBT.hpp"
#include "utils.hpp"
#include <memory>
namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		public:
			typedef Key			key_type;
			typedef Key			value_type;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;
			typedef Compare		key_compare;
			typedef Compare		value_type;
			typedef Allocator	allocator_type;

			typedef RBT<value_type, key_compare, allocator_type> tree_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef typename ft::RBT_iterator<typename tree_type::node, tree_type>			iterator;
			typedef typename ft::const_RBT_iterator<typename tree_type::node, tree_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		private:
			ft::RBT<value_type, key_compare, allocator_type>	_tree;
			key_compare											_compare;
			allocator_type										_allocator;

		public:
			explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _tree(comp, alloc), _compare(comp), _allocator(alloc) {}

			template<class InputIt>
			set(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc), _compare(comp), _allocator(alloc)
			{
				this->_tree.insert(first, last);
			}

			set(const set& other)
			{
				*this = other;
			}
	};

} // ft namespace

#endif
