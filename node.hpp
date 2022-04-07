/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:15:46 by elona             #+#    #+#             */
/*   Updated: 2022/04/07 17:53:29 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#define BLACK	0
#define RED		1

namespace ft
{
	struct end_node
	{
		typedef struct end_node*			pointer;
		typedef struct end_node&			reference;
		typedef const struct end_node&		const_reference;

		pointer		left;
		end_node(void) : left(NULL) {}
		end_node(pointer l) : left(l) {}
		end_node(const_reference src) : left(src.left) {}
		reference	operator=(const_reference src) { left = src.left; return (*this);}
		~end_node(void){}
	};
	
	struct base_node : public end_node
	{
		typedef struct base_node*			pointer;
		typedef struct base_node&			reference;
		typedef const struct base_node&		const_reference;

		pointer	parent;
		pointer	right;
		bool	color;
		base_node(void) : parent(NULL), right(NULL), color(RED) {}
		// base_node(pointer  p, pointer r, pointer l, bool cl) : end_node(l), parent(p), right(r), color(cl) {}
		base_node(const_reference src) : parent(NULL), right(NULL), color(RED) { *this = src;}
		reference operator=(const_reference src)
		{
			if (this == &src)
				return ;
			left = src.left;
			parent = src.parent;
			right = src.right;
			color = src.color;
			return (*this);
		}
		~base_node(void){}
	};
	
	template <typename T>
	struct node : base_node
	{
		typedef T						value_type;
		typedef struct node*			pointer;
		typedef struct node&			reference;
		typedef const struct node&		const_reference;
		
		value_type	data;
		node(void) : data(){}
		node(value_type data) : data(data){}
		node(const_reference src) : base_node(src), data(data) {}
		~node() {}
	};
}