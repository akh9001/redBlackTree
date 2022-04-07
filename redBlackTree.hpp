/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 01:20:50 by akhalidy          #+#    #+#             */
/*   Updated: 2022/04/07 18:53:56 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "node.hpp"

template <typename T, typename Compare, typename Alloc>
class redBlackTree
{
		
	public:
		typedef T											value_type;
		typedef typename value_type::first_type				first_type;
		typedef typename value_type::second_type			second_type;
		typedef Compare										key_compare;
		typedef	ft::end_node								end_node;
		typedef	ft::base_node								base_node;
		typedef	ft::node<value_type>						node;
		typedef	Alloc::template rebind<node>::other			alloc_type;
		redBlackTree(/* args */) : nil() {}
		~redBlackTree();
	private:
		Compare		less;
		end_node	nil;
};

// redBlackTree::redBlackTree(/* args */)
// {
// }

// redBlackTree::~redBlackTree()
// {
// }
