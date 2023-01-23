/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:54:10 by jsubel            #+#    #+#             */
/*   Updated: 2023/01/23 16:50:58 by jsubel           ###   ########.fr       */
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
		typedef typename T value_type;
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


		RBT(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			this->_compare = comp;
			this->_allocator = alloc;
			this->_size = 0;

			// make empty end
			this->_end = this->_nodeAlloc.allocate(1);
			this->_end->_content= this->_allocator.allocate(1);
			this->_allocator.construct(this->_end->content);
			this->_end->color.BLACK;
			this->_end->parent = NULL;
			this->_end->left_child = NULL;
			this->_end->right_child = NULL;

			// make empty reverse end
			this->_rend = this->_nodeAlloc.allocate(1);
			this->_rend->_content= this->_allocator.allocate(1);
			this->_allocator.construct(this->_rend->content);
			this->_rend->color.BLACK;
			this->_rend->parent = NULL;
			this->_rend->left_child = NULL;
			this->_rend->right_child = NULL;

			this->_root = this->_end;
		}

		RBT(const RBT &rhs)
		{
			*this = rhs;
		}

		~RBT()
		{

		}

		RBT &operator=(const RBT &rhs)
		{
			this->clear();
			this->_compare = rhs.getCompare();
			this->_allocator = rhs.getAllocator();
			this->_size = rhs.size();
			if (rhs.getRoot() != rhs.getEnd())
			{
				this->_root = this->_nodeAlloc.allocate(1);
				this->_root->parent = NULL;
				this->_root->left_child = NULL;
				this->_root->right_child = NULL;
				this->_root->color = BLACK;
				this->_root->content = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root->content, *(rhs.getRoot()->content));
				this->copySubtree(this->_root, rhs.getRoot());
			}
			this->_end->parent = this->max(this->_root);
			this->_rend->parent = this->min(this->_root);
		}

		// copy the subtrees starting at a specified nodeSrc to the node located at nodeDest
		// checks for left and right childen and if they exist, allocates and sets them to the correct values
		// then, calls itself on the newly created child
		void copySubTree(node_pointer nodeDest, node_pointer nodeSrc)
		{
			if (nodeSrc->left_child)
			{
				nodeDest->left_child = this->_nodeAlloc.allocate(1);
				nodeDest->left_child->parent = nodeDest;
				nodeDest->left_child->left_child = NULL;
				nodeDest->left_child->right_child = NULL;
				nodeDest->left_child->color = nodeSrc->left_child->color;
				nodeDest->left_child->content = this->_allocator.allocate(1);
				this->_allocator.construct(nodeDest->left_child->content, *(nodeSrc->left_child->content));
				copySubtree(nodeDest->left_child, nodeSrc->left_child);
			}
			if (nodeSrc->right_child)
			{
				nodeDest->right_child = this->_nodeAlloc.allocate(1);
				nodeDest->right_child->parent = nodeDest;
				nodeDest->right_child->left_child = NULL;
				nodeDest->right_child->right_child = NULL;
				nodeDest->right_child->color = nodeSrc->right_child->color;
				nodeDest->right_child->content = this->_allocator.allocate(1);
				this->_allocator.construct(nodeDest->right_child->content, *(nodeSrc->right_child->content));
				copySubtree(nodeDest->right_child, nodeSrc->right_child);
			}
		}

		/**
		 * to insert a node into a Red Black Tree, 4 cases are possible
		 * Case 1: the tree is empty at the beginning
		 * 	in that case, make the new element the root element and thus BLACK
		 * Case 2: if the tree is not empty, create a new leaf in RED
		 * 	if the parent of that new node is BLACK, exit the function
		 * Case 3: if the parent of that new node is RED, check for its siblings
		 * 	3.1: sibling is BLACK or NULL
		 * 		find the suitable rotation & relocoring
		 * 		LL/RR rotation: recolor grandparent and parent
		 * 		LR/RL rotation: recolor grandparent and child
		 * 	3.2: sibling is RED
		 * 		recolor BOTH siblings & check if the grandparent is root
		 * 		if not: recolor it and recheck it
		*/
		node_pointer insert(value_type val)
		{
			// first check if node already exists
			// still have to do that, probably with find?
			node_pointer new_node = this->_nodeAlloc.allocate(1);
			new_node->content = this->_allocator.allocate(1);
			this->_allocator.construct(new_node->content, val);
			this->_size++;
			new_node->parent = NULL;
			new_node->left_child = NULL;
			new_node->right_child = NULL;
			// Case 1
			if (this->_root == this->_end)
			{
				new_node->color = BLACK;
				new_node->parent = NULL;
				this->_root = new_node;
				this->_end->parent = new_node;
				this->_rend->parent = new_node;
				return (new_node);
			}
			// Case 2
			new_node->color = RED;
			BST_insertion(new_node);
			node_pointer	check_node = new_node;
			// Cases 3
			while (check_node->parent && check_node->parent->color == RED)
			{
				// Case 3.2
				node_pointer grandparent = check_node->parent->parent;
				if (this->sibling(check_node->parent)->color == RED)
				{
					recolor(check_node->parent);
					recolor(this->sibling(check_node->parent));
					if (grandparent != this->_root)
					{
						recolor(grandparent);
					}
					check_node = grandparent;
				}
				else
				{
					// LR or RR
					if (check_node->parent == grandparent->left_child)
					{
						if (check_node == check_node->parent->right_child)
						{
							check_node = check_node->parent;
							rotate_left(check_node);

						}
						rotate_right(check_node->parent->parent);
						recolor(check_node->parent);
						recolor(check_node->parent->right_child);
					}
					// RL or LL
					else
					{
						if (check_node == check_node->parent->left_child)
						{
							check_node = check_node->parent;
							rotate_right(check_node);
						}
						rotate_left(check_node->parent->parent);
						recolor(check_node->parent);
						recolor(check_node->left_child);
					}
				}
			}
			this->_end->parent = this->max(this->_root);
			this->_rend->parent = this->min(this->_root);
			return (check_node);
		}

		void recolor(node_pointer node)
		{
			if (!node)
				return ;
			node->color = !node->color;
		}


		node_pointer getRoot() const
		{
			return (this->_root);
		}

		node_pointer getEnd() const
		{
			return (this->_end);
		}

		node_pointer getRend() const
		{
			return (this->_rend);
		}

		allocator_type getAllocator() const
		{
			return (this->_allocator);
		}

		key_compare getCompare() const
		{
			return (this->_compare);
		}

		size_type size() const
		{
			return (this->_size);
		}

		size_type max_size() const
		{
			return (this->_allocator.max_size());
		}

		node_pointer max(node_pointer node) const
		{
			node_pointer temp;
			temp = node;
			if (!this->_root)
				return (this->_end);
			while (temp->right_child)
				temp = temp->right_child;
			return (temp);
		}

		node_pointer min(node_pointer node) const
		{
			node_pointer temp;
			temp = node;
			if (!this->_root)
				return (this->_end);
			while (temp->left_child)
				temp = temp->left_child;
			return (temp);
		}

		iterator begin()
		{
			return (iterator(this->min(this->_root), this->_end, this->_rend));
		}

		iterator end()
		{
			return (iterator(this->_end, this->_end, this->_rend));
		}

		iterator rend()
		{
			return (iterator(this->_rend, this->_end, this->_rend));
		}

		const_iterator begin()
		{
			return (const_iterator(this->min(this->_root), this->_end, this->_rend));
		}

		const_iterator end()
		{
			return (const_iterator(this->_end, this->_end, this->_rend));
		}

		const_iterator rend()
		{
			return (const_iterator(this->_rend, this->_end, this->_rend));
		}

		bool is_left_son(node_pointer node) const
		{
			if (node->parent && node->parent->left == node)
				return (true);
			return (false);
		}

		bool is_right_son(node_pointer node) const
		{
			if (node->parent && node->parent->right == node)
				return (true);
			return (false);
		}

		node_pointer sibling(node_pointer node)
		{
			if (node == NULL)
				return (NULL);
			if (node->parent == NULL)
				return (NULL);
			return (is_left_son(node) ? node->parent->right : node->parent->left);
		}

		// passed node is the root of the subtree to be rotated and thus the initial parent
		// pivot is the child that takes the root node's place
		void rotate_left(node_pointer node)
		{
			node_pointer pivot = node->right_child;
			node->right_child = pivot->left_child;
			if (pivot->left_child)
				pivot->left_child->parent = node;
			if (!node->parent)
				this->_root = pivot;
			else if (is_left_son(node))
				node->parent->lc = pivot;
			else
				node->parent->rc = pivot;
			pivot->left_child = node;
			node->parent = pivot;
		}

		void rotate_right(node_pointer node)
		{
			node_pointer pivtor = node->left_child;
			node->left_child = pivtor->right_child;
			if (pivtor->right_child)
				pivtor->right_child->parent = node;
			if (!node->parent)
				this->_root = pivtor;
			else if (is_right_son(node))
				node->parent->lc = pivtor;
			else
				node->parent->rc = pivtor;
			pivtor->right_child = node;
			node->parent = pivtor;
		}

		void BST_insertion(node_pointer node)
		{
			node_pointer current = this->_root;
			while(current)
			{
				// compare node key and currently looked at key according to comparsion function
				if (this->_compare(get_key(node->content), (current->content)))
				{
					// if there is a left child, take this as new currently looked at key and loop
					if (current->left_child)
						current = current.left_child;
					else
					{
						// set pointers in the nodes accordingly
						current->left_child = node;
						node->parent = current;
						return ;
					}
				}
				else
				{
					// same logic as above
					if (current->right_child)
						current = current.right_child;
					else
					{
						current->right_child = node;
						node->parent = current;
						return ;
					}
				}
			}
		}

		void recolor(node_pointer node)
		{
			if (!node)
				return ;
			node->color = !node->color;
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
