/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:54:10 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/13 15:54:51 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include "utils.hpp"
#include "RBT_iterator.hpp"
#include <memory>
#include <iostream>

#define RED		true
#define BLACK	false

namespace ft
{

template<typename T>
struct Node
{
	public:
		T		*content;
		Node	*parent;
		Node	*left_child;
		Node	*right_child;
		bool	color;
};

template<typename T>
struct ConstNode
{
	public:
		ConstNode(Node<T> node) : content(node->content), parent(node->parent), left_child(node->left_child), right_child(node->right_child), color(node->color) {}
		T		*content;
		Node	*parent;
		Node	*left_child;
		Node	*right_child;
		bool	color;
};

template<typename T, typename Compare, typename Alloc = std::allocator<T>>
class RBT
{
	public:
		typedef T				value_type;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		typedef Compare			key_compare;

		typedef Alloc			allocator_type;
		typedef Node<T>			node;
		typedef Node<T>			*node_pointer;
		typedef Node<const T>	*const_node_pointer;

		typedef RBT<value_type, key_compare, allocator_type>		tree_type;

		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename ft::RBT_iterator<node, tree_type>			iterator;
		typedef typename ft::const_RBT_iterator<node, tree_type>	const_iterator;

		bool		empty() const
		{
			return (_root == NULL);
		}
		iterator	max()
		{
			return ()
		}


	private:
		node_pointer			_root;
		node_pointer			_end;
		node_pointer			_rend;
		allocator_type			_allocator;
		std::allocator<Node<T>>	_nodeAlloc;
		key_compare				_compare;
		size_type				_size;
}

} // namespace ft

#endif
