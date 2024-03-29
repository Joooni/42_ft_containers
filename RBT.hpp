/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:54:10 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/27 14:09:27 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP

#include "utils.hpp"
#include "RBT_iterator.hpp"
#include <memory>
#include <iostream>
#include <algorithm>
#include <cstddef>

#include "colors.hpp"

#define RED true
#define BLACK false

#include <sstream>

namespace ft
{

	template <typename T>
	struct Node
	{
	public:
		T *content;
		Node *parent;
		Node *left_child;
		Node *right_child;
		bool color;
	};

	template <typename T>
	struct ConstNode
	{
	public:
		ConstNode(Node<T> node) : content(node->content), parent(node->parent), left_child(node->left_child), right_child(node->right_child), color(node->color) {}
		T * const	content;
		ConstNode	*parent;
		ConstNode	*left_child;
		ConstNode	*right_child;
		bool		color;
	};


	template <typename T, typename Compare, typename Alloc = std::allocator<T> >
	class RBT
	{
	public:
		typedef T			value_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef Compare		key_compare;

		typedef Alloc			allocator_type;
		typedef Node<T>			node;
		typedef Node<T>			*node_pointer;
		typedef Node<const T>	*const_node_pointer;

		typedef RBT<value_type, key_compare, allocator_type> tree_type;

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

			// make empty end
			this->_end = this->_nodeAlloc.allocate(1);
			this->_end->content = this->_allocator.allocate(1);
			this->_allocator.construct(this->_end->content);
			this->_end->color = BLACK;
			this->_end->parent = NULL;
			this->_end->left_child = NULL;
			this->_end->right_child = NULL;

			// make empty reverse end
			this->_rend = this->_nodeAlloc.allocate(1);
			this->_rend->content = this->_allocator.allocate(1);
			this->_allocator.construct(this->_rend->content);
			this->_rend->color = BLACK;
			this->_rend->parent = NULL;
			this->_rend->left_child = NULL;
			this->_rend->right_child = NULL;

			this->_root = this->_end;
			this->_size = 0;
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
			return (*this);
		}

		// copy the subtrees starting at a specified nodeSrc to the node located at nodeDest
		// checks for left and right childen and if they exist, allocates and sets them to the correct values
		// then, calls itself on the newly created child
		void copySubtree(node_pointer nodeDest, node_pointer nodeSrc)
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
			node_pointer already_found = find_node(val);
			if (already_found != this->_end)
				return (already_found);
			node_pointer new_node = this->_nodeAlloc.allocate(1);
			node_pointer original_node = new_node;
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
				this->_end->parent = this->_root;
				this->_rend->parent = this->_root;
				return (new_node);
			}
			new_node->color = RED;
			BST_insertion(new_node);
			// Case 3 (2 immediately not fulfills while condition)
			while (new_node->parent && new_node->parent->color == RED)
			{
				// Case 3.1: both parent and parents sibling are red
				if (new_node->parent->parent->left_child && new_node->parent->parent->right_child && new_node->parent->parent->left_child->color == RED && new_node->parent->parent->right_child->color == RED)
				{
					if (new_node->parent->parent != this->_root)
						recolor(new_node->parent->parent);
					recolor(new_node->parent->parent->left_child);
					recolor(new_node->parent->parent->right_child);
					new_node = new_node->parent->parent;
				}
				else // Case 3.2
				{
					// RL or LL
					if (new_node->parent == new_node->parent->parent->right_child)
					{
						if (new_node == new_node->parent->left_child)
						{
							new_node = new_node->parent;
							rotate_right(new_node);
						}
						rotate_left(new_node->parent->parent);
						recolor(new_node->parent);
						recolor(new_node->parent->left_child);
					}
					else // LR or RR
					{
						if (new_node == new_node->parent->right_child)
						{
							new_node = new_node->parent;
							rotate_left(new_node);
						}
						rotate_right(new_node->parent->parent);
						recolor(new_node->parent);
						recolor(new_node->parent->right_child);
					}
				}
			}
			this->_end->parent = this->max(this->_root);
			this->_rend->parent = this->min(this->_root);
			return (original_node);
		}

		/**
		 * walk through the entire tree, starting at the root
		 * and then compare current element with the key/value
		 * to see if it is the node we were looking for
		 * or in which subtree it is located
		*/
		template <typename Key>
		node_pointer find_node(Key k) const
		{
			node_pointer find_node = this->_root;
			if (find_node == this->_end)
				return (this->_end);
			while (find_node)
			{
				if (k == get_key(find_node->content))
				{
					return (find_node);
				}
				else if (this->_compare(k, get_key(find_node->content)))
				{
					if (find_node->left_child)
						find_node = find_node->left_child;
					else
						return (this->_end);
				}
				else
				{
					if (find_node->right_child)
						find_node = find_node->right_child;
					else
						return (this->_end);
				}
			}
			return (this->_end);
		}

		node_pointer find_node(value_type val) const
		{
			node_pointer find_node = this->_root;
			if (find_node == this->_end)
				return (this->_end);
			while (find_node)
			{
				if (get_key(&val) == get_key(find_node->content))
				{
					return (find_node);
				}
				else if (this->_compare(get_key(&val), get_key(find_node->content)))
				{
					if (find_node->left_child)
						find_node = find_node->left_child;
					else
						return (this->_end);
				}
				else
				{
					if (find_node->right_child)
						find_node = find_node->right_child;
					else
						return (this->_end);
				}
			}
			return (this->_end);
		}

		node_pointer predecessor(node_pointer node) const
		{
			if (node == this->_end)
				return (this->max(this->_root));
			if (node->left_child)
				return (max(node->left_child));
			while (is_left_son(node))
				node = node->parent;
			return ((node->parent));
		}

		node_pointer successor(node_pointer node) const
		{
			if (node == this->max(this->_root))
				return ((this->_end));
			if (node->right_child)
				return (min(node->right_child));
			while (is_right_son(node))
				node = node->parent;
			return ((node->parent));
		}

		void erase(value_type &val)
		{
			node_pointer node = this->find_node(val);
			if (node == this->_end || node == this->_rend)
				return ;
			if (node == this->max(this->_root))
				this->_end->parent = this->predecessor(this->max(this->_root));
			else if (node == this->min(this->_root))
				this->_rend->parent = this->successor(this->min(this->_root));
			this->erase(node);
		}


		template<typename Key>
		size_type erase (Key &key)
		{
			node_pointer node = this->find_node<Key>(key);
			if (node == this->_end || node == this->_rend)
				return (0);
			if (node == this->max(this->_root))
				this->_end->parent = this->predecessor(this->max(this->_root));
			else if (node == this->min(this->_root))
				this->_rend->parent = this->successor(this->min(this->_root));
			this->erase(node);
			return (1);
		}

		/** similar to BST deletion, but with more specific cases
		 * three base cases that might get more specific
		 *  Case 0: tree only has one element at root - delete it and set tree to 0
		 * 	Case 1: node has up to one child - just replace it with its child or a NIL node
		 * 	Case 2: node has two children - find nodes successor and have it take nodes position in the tree
		 * 		in that case, the original subtrees of node become the subtrees of the new node
		*/
		void erase(node_pointer node)
		{
			if (!this->_root->left_child && !this->_root->right_child && this->_root != this->_end)
			{
				deleteNode(this->_root);
				this->_root = this->_end;
				this->_size--;
				return ;
			}
			node_pointer moved_node;
			bool erasednode_color;
			this->_size--;
			if (!node->left_child || !node->right_child)
			{
				erasednode_color = node->color;
				moved_node = transplant(node);
			}
			else
			{
				node_pointer successor = this->successor(node);
				this->_allocator.destroy(node->content);
				this->_allocator.construct(node->content, *(successor->content));
				erasednode_color = successor->color;
				moved_node = transplant(successor);
			}
			if (erasednode_color == BLACK)
			{
				fixErase(moved_node);
			}
			if (moved_node && !moved_node->content)
			{

				if (moved_node == moved_node->parent->left_child)
					moved_node->parent->left_child = NULL;
				else if (moved_node == moved_node->parent->right_child)
					moved_node->parent->right_child = NULL;
				this->_nodeAlloc.deallocate(moved_node, 1);
			}
		}

		void fixErase(node_pointer node)
		{
			if (node == this->_root)
			{
				node->color = BLACK;
				return ;
			}
			node_pointer sibling_node = sibling(node);
			if (sibling_node->color == RED)
			{
				sibling_node->color = BLACK;
				node->parent->color = RED;
				if (node == node->parent->left_child)
					rotate_left(node->parent);
				else
					rotate_right(node->parent);
				sibling_node = sibling(node);
			}
			if (isBlack(sibling_node->left_child) && isBlack(sibling_node->right_child))
			{
				sibling_node->color = RED;
				if (node->parent->color == RED)
					node->parent->color = BLACK;
				else
					fixErase(node->parent);
			}
			else
			{
				if (is_left_son(node) && isBlack(sibling_node->right_child))
				{
					sibling_node->left_child->color = BLACK;
					sibling_node->color = RED;
					rotate_right(sibling_node);
					sibling_node = node->parent->right_child;
				}
				else if (!is_left_son(node) && isBlack(sibling_node->left_child))
				{
					sibling_node->right_child->color = BLACK;
					sibling_node->color = RED;
					rotate_left(sibling_node);
					sibling_node = node->parent->left_child;
				}
				sibling_node->color = node->parent->color;
				node->parent->color = BLACK;
				if (is_left_son(node))
				{
					sibling_node->right_child->color = BLACK;
					rotate_left(node->parent);
				}
				else
				{
					sibling_node->left_child->color = BLACK;
					rotate_right(node->parent);
				}
			}
		}

		bool isBlack(node_pointer node)
		{
			return (!node || node->color == BLACK);
		}

		/**
		 * subroutine to erase a node that has less than two children
		 * if a child exists, calls delete_with_one_child
		 * otherwise, either just deletes (if its a RED node)
		 * or replaces with a NULL node (if its a BLACK node) and then deletes it
		 * returns pointer to deleted node
		 * */
		node_pointer transplant(node_pointer node)
		{
			node_pointer temp;
			if (node->left_child || node->right_child)
			{
				return (delete_with_one_child(node));
			}
			else if (node->color == RED)
			{
				deleteNode(node);
				return (NULL);
			}
			else
			{
				temp = this->_nodeAlloc.allocate(1);
				temp->color = BLACK;
				temp->left_child = NULL;
				temp->right_child = NULL;
				temp->content = NULL;
				temp->parent = node->parent;
				if (is_left_son(node))
					node->parent->left_child = temp;
				else
					node->parent->right_child = temp;
				deleteNode(node);
				return (temp);
			}
	}


	node_pointer delete_with_one_child(node_pointer node)
	{
		node_pointer child;
		if (node->left_child)
			child = node->left_child;
		else if (node->right_child)
			child = node->right_child;
		else
			return (NULL);
		node->color = child->color;
		this->_allocator.destroy(node->content);
		this->_allocator.construct(node->content, *(child->content));
		deleteNode(child);
		return (node);
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

		const_iterator begin() const
		{
			return (const_iterator(this->min(this->_root), this->_end, this->_rend));
		}

		const_iterator end() const
		{
			return (const_iterator(this->_end, this->_end, this->_rend));
		}

		const_iterator rend() const
		{
			return (const_iterator(this->_rend, this->_end, this->_rend));
		}

		bool is_left_son(node_pointer node) const
		{
			if (node->parent && node == node->parent->left_child)
				return (true);
			return (false);
		}

		bool is_right_son(node_pointer node) const
		{

			if (node->parent && node == node->parent->right_child)
				return (true);
			return (false);
		}

		node_pointer sibling(node_pointer node)
		{
			if (node == NULL)
				return (NULL);
			if (node->parent == NULL)
				return (NULL);
			return (is_left_son(node) ? node->parent->right_child : node->parent->left_child);
		}

		void swap(RBT &rhs)
		{
			node_pointer temp_root = this->_root;
			node_pointer temp_end = this->_end;
			node_pointer temp_rend = this->_rend;
			allocator_type temp_alloc = this->_allocator;
			key_compare temp_compare = this->_compare;
			size_type temp_size = this->_size;

			this->_root = rhs._root;
			this->_end = rhs._end;
			this->_rend = rhs._rend;
			this->_allocator = rhs._allocator;
			this->_compare = rhs._compare;
			this->_size = rhs._size;

			rhs._root = temp_root;
			rhs._end = temp_end;
			rhs._rend = temp_rend;
			rhs._allocator = temp_alloc;
			rhs._compare = temp_compare;
			rhs._size = temp_size;
		}

		void printTree(void) const
		{
			printRBT("", this->_root, false);
		}

		void clear()
		{
			this->clearSubtree(this->_root);
			this->_root = this->_end;
			this->_size = 0;
		}

		void deleteEnds()
		{
			this->_allocator.destroy(this->_end->content);
			this->_allocator.deallocate(this->_end->content, 1);
			this->_nodeAlloc.deallocate(this->_end, 1);
			this->_allocator.destroy(this->_rend->content);
			this->_allocator.deallocate(this->_rend->content, 1);
			this->_nodeAlloc.deallocate(this->_rend, 1);
		}


	private:
		node_pointer				_root;
		node_pointer				_end;
		node_pointer				_rend;
		allocator_type				_allocator;
		std::allocator< Node<T> >	_nodeAlloc;
		key_compare					_compare;
		size_type					_size;


		// // passed node is the root of the subtree to be rotated and thus the initial parent
		// // pivot is the child that takes the root node's place
		void rotate_left(node_pointer node)
		{
			node_pointer pivot = node->right_child;
			node->right_child = pivot->left_child;
			if (pivot->left_child)
				pivot->left_child->parent = node;
			pivot->parent = node->parent;
			if (!node->parent)
				this->_root = pivot;
			else if (is_left_son(node))
				node->parent->left_child = pivot;
			else
				node->parent->right_child = pivot;
			pivot->left_child = node;
			node->parent = pivot;
		}

		void rotate_right(node_pointer node)
		{
			node_pointer pivot = node->left_child;
			node->left_child = pivot->right_child;
			if (pivot->right_child)
				pivot->right_child->parent = node;
			pivot->parent = node->parent;
			if (!node->parent)
				this->_root = pivot;
			else if (is_right_son(node))
				node->parent->right_child = pivot;
			else
				node->parent->left_child = pivot;
			pivot->right_child = node;
			node->parent = pivot;
		}

		void recolor(node_pointer node)
		{
			if (!node)
				return;
			node->color = !node->color;
		}

		void printRBT(const std::string& prefix, const node_pointer node, bool isLeft) const
		{
			if( node != NULL )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├───" : "└───" );

				// print the value of the node
				std::cout << (node->color == BLACK ? COLOR_BRIGHT_DARK_GREY : COLOR_BRIGHT_RED ) << (*node->content).first << "/" << (*node->content).second << END << std::endl;

				// enter the next tree level - left and right branch
				printRBT( prefix + (isLeft ? "│   " : "    "), node->left_child, true);
				printRBT( prefix + (isLeft ? "│   " : "    "), node->right_child, false);
			}
		}

		void clearSubtree(node_pointer node)
		{
			if (!node || node == this->_end)
				return ;
			if (node->left_child)
				clearSubtree(node->left_child);
			if (node->right_child)
				clearSubtree(node->right_child);
			deleteNode(node);
		}

		void deleteNode(node_pointer node)
		{
			if (!node)
				return ;
			if (node->parent)
			{
				if (node == node->parent->left_child)
					node->parent->left_child = NULL;
				else if (node == node->parent->right_child)
					node->parent->right_child = NULL;
			}
			this->_allocator.destroy(node->content);
			this->_allocator.deallocate(node->content, 1);
			this->_nodeAlloc.deallocate(node, 1);
		}

		void BST_insertion(node_pointer node)
		{
			node_pointer current = this->_root;
			while (current)
			{
				// compare node key and currently looked at key according to comparsion function
				if (this->_compare(get_key(node->content), get_key(current->content)))
				{
					// if there is a left child, take this as new currently looked at key and loop
					if (current->left_child)
						current = current->left_child;
					else
					{
						// set pointers in the nodes accordingly
						current->left_child = node;
						node->parent = current;
						return;
					}
				}
				else
				{
					// same logic as above
					if (current->right_child)
						current = current->right_child;
					else
					{
						current->right_child = node;
						node->parent = current;
						return;
					}
				}
			}
		}

		void deleteFix(node_pointer node)
		{
			node_pointer sibling_node;
			while (node != this->_root && node->color == BLACK)
			{
				if (is_left_son(node))
				{
					sibling_node = sibling(node);
					// Case 1: node sibling is RED
					// switch colors of sibling and parent
					// and perform left rotation,
					// transforming this into Cases 2, 3, or 4
					// depending on their childrens' colors
					if (sibling_node->color == RED)
					{
						sibling_node->color = BLACK;
						node->parent->color = RED;
						rotate_left(node->parent);
						sibling_node = sibling(node);
					}
					// Case 2: both sibling of node AND childen of sibling are black
					if (sibling_node->left_child->color == BLACK && sibling_node->right_child->color == BLACK)
					{
						sibling_node->color = RED;
						node = node->parent;
					}
					else
					{
						// Case 3: only right child is black
						// transforms into Case 4
						if (sibling_node->right_child->color == BLACK)
						{
							sibling_node->left_child->color = BLACK;
							sibling_node->color = RED;
							rotate_right(sibling_node);
							sibling_node = sibling(node);
						}
						// Case 4: right child is red
						sibling_node->color = node->parent->color;
						node->parent->color = BLACK;
						sibling_node->right_child->color = BLACK;
						rotate_left(node->parent);
						node = this->_root;
					}
				}
				else // same as before, just for the right subtree
				{
					sibling_node = sibling(node);
					if (sibling_node->color == RED)
					{
						sibling_node->color = BLACK;
						node->parent->color = RED;
						rotate_right(node->parent);
						sibling_node = sibling(node);
					}
					if (sibling_node->right_child->color == BLACK && sibling_node->left_child->color == BLACK)
					{
						sibling_node->color = RED;
						node = node->parent;
					}
					else
					{
						if (sibling_node->left_child->color == BLACK)
						{
							sibling_node->right_child->color = BLACK;
							sibling_node->color = RED;
							rotate_left(sibling_node);
							sibling_node = sibling(node);
						}
						sibling_node->color = node->parent->color;
						node->parent->color = BLACK;
						sibling_node->left_child->color = BLACK;
						rotate_right(node->parent);
						node = this->_root;
					}
				}
			}
			node->color = BLACK;
		}


	};

} // namespace ft

#endif
