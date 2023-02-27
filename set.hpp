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

			~set()
			{
				this->_tree.clear();
				this->_tree.deleteEnds();
			}

			set(const set &other)
			{
				*this = other;
			}

			set &operator=(const set &other)
			{
				this->_allocator = other._allocator;
				this->_compare = other._compare;
				this->clear();
				this->_tree = other._tree;
				return (*this);
			}

			allocator_type get_allocator() const
			{
				return (this->_allocator);
			}

			iterator begin()
			{
				return (this->_tree.begin());
			}

			iterator end()
			{
				return (this->_tree.end());
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_tree.end()))
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->_tree.begin()));
			}

			const_iterator begin() const
			{
				return (this->_tree.begin());
			}

			const_iterator end() const
			{
				return (this->_tree.end());
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_tree.end()))
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_tree.begin()));
			}

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
				return (this->_allocator.max_size());
			}

			void clear()
			{
				this->_tree.clear();
			}

			ft::pair<iterator, bool> insert(const value_type &value)
			{
				bool temp_bool = (this->_tree.find_node(value)) == this->_tree.getEnd();
				iterator temp_iter = iterator(this->_tree.insert(value), this->_tree.getEnd(), this->_tree.getRend());
				return (ft::make_pair<iterator, bool>(temp_iter, temp_bool));
			}

			iterator insert(iterator pos, const value_type &value)
			{
				(void)pos;
				return (insert(value).first);
			}

			template<class InputIt>
			void insert(InputIt first, InputIt last)
			{
				while (first != last)
					this->_tree.insert(*(first++));
			}

			void erase(iterator pos)
			{
				this->_tree.erase(*pos);
			}

			void erase(iterator first, iterator last)
			{
				set<value_type> temp_set(first, last);
				for (iterator it = temp_set.begin(); it != temp_set.end(); ++it)
					this->erase(it);
			}

			size_type erase(const key_type &key)
			{
				return (this->_tree.erase(key));
			}

			void swap(set &other)
			{
				this->_tree.swap(other._tree);
			}

			size_type count(const key_type &key) const
			{
				if (this->find(key) == this->end())
					return (0);
				else
					return (1);
			}

			iterator find (const key_type &key)
			{
				return (iterator(this->_tree.template find_node<key_type>(key), this->_tree.getEnd(), this->_tree.getRend()));
			}

			const_iterator find(vonst key_type &key) const
			{
				return (const_iterator(this->_tree.template find_node<key_type>(key), this->_tree.getEnd(), this->_tree.getRend()));
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

		private:

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal<typename ft::set<Key, T>::const_iterator, typename ft::set<Key, T>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare<typename ft::set<Key, T>::const_iterator, typename ft::set<Key, T>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const set<Key, T, Compare, Alloc> &lhs, const set<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

} // namespace ft

namespace std
{
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::set<Key,T,Compare,Alloc>& lhs, ft::set<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
