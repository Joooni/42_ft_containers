/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:39:36 by jsubel            #+#    #+#             */
/*   Updated: 2023/02/16 14:35:14 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include "RBT.hpp"
#include "utils.hpp"
#include <memory>
// checking out STL
// #include <map>
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

		explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _allocator(alloc)
		{

		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _allocator(alloc)
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
			this->_tree.deleteEnds();
		}

		//-*-*-*-*-*-*-*-*-*-//
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
			return((*((this->insert(ft::make_pair(key, mapped_type()))).first)).second);
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
			return (rIter);
		}

		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator rIter(this->end());
			return (rIter);
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(this->_tree.begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->_tree.begin()));
		}

		//-*-*-*-*-*-*-*-*-*-//
		//      Capacity     //
		//-*-*-*-*-*-*-*-*-*-//

		bool empty() const
		{
			return (!this->size());
		}

		size_type size() const
		{
			return (this->_tree.size());
		}

		size_type max_size() const
		{
			return (this->_tree.max_size());
		}

		//-*-*-*-*-*-*-*-*-*-//
		//      Modifier     //
		//-*-*-*-*-*-*-*-*-*-//

		void clear()
		{
			this->_tree.clear();
		}

		// inserts value
		pair<iterator, bool> insert(const value_type &value)
		{
			bool temp_bool = (this->_tree.find_node(value)) == this->_tree.getEnd();
			iterator temp_iter = iterator(this->_tree.insert(value), this->_tree.getEnd(), this->_tree.getRend());
			return (ft::make_pair<iterator, bool>(temp_iter, temp_bool));
		}

		// inserts value as close as possible to position prior to pos
		// but... its a BST. there is only one right space for it to go
		iterator insert(iterator pos, const value_type &value)
		{
			(void)pos;
			return (insert(value).first);
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
			{
				this->_tree.insert(*first);
				++first;
			}
		}

		void erase(iterator pos)
		{
			iterator temp(pos);
			++temp;
			this->_tree.erase(*pos);
			return (temp);
		}

		void erase(iterator first, iterator last)
		{
			map<key_type, mapped_type> temp(first, last);
			for (iterator it = temp.begin(); it != temp.end(); ++it)
				this->erase(it->first);
			return (last);
		}

		size_type erase(const key_type &key)
		{
			return (this->_tree.erase(key));
		}

		void swap(map &other)
		{
			this->_tree.swap(other._tree);
		}

		size_type count(const key_type &key) const
		{
			return ((this->find(key) == this->end()) ? 0 : 1);
		}

		iterator find (const key_type& key)
		{
			return (iterator(this->_tree.template find_node<key_type>(key), this->_tree.getEnd(), this->_tree.getRend()));
		}

		const_iterator find (const key_type& key) const
		{
			return (const_iterator(this->_tree.template find_node<const key_type>(key), this->_tree.getEnd(), this->_tree.getRend()));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}

		iterator lower_bound(const key_type &key)
		{
			iterator it = this->begin();
			while (it != this->end() && (this->_compare(it->first, key)))
				++it;
			return (it);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator it = this->begin();
			while (it != this->end() && (this->_compare(it->first, key)))
				++it;
			return (it);
		}

		iterator upper_bound(const key_type &key)
		{
			iterator it = this->begin();
			while (it != this->end() && !(this->_compare(key, it->first)))
				++it;
			return (it);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator it = this->begin();
			while (it != this->end() && !(this->_compare(key, it->first)))
				++it;
			return (it);
		}

		key_compare key_comp() const
		{
			return (this->_compare);
		}

		value_compare value_comp() const
		{
			return (value_compare(this->_compare));
		}

		void printTree() const
		{
			this->_tree.printTree();
		}
};

//-*-*-*-*-*-*-*-*-*-//
//Operator overloads //
//-*-*-*-*-*-*-*-*-*-//


template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal<typename ft::map<Key, T>::const_iterator, typename ft::map<Key, T>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(lhs == rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (ft::lexicographical_compare<typename ft::map<Key, T>::const_iterator, typename ft::map<Key, T>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(rhs < lhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

namespace std
{
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
