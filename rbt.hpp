/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 01:13:02 by akhalidy          #+#    #+#             */
/*   Updated: 2022/04/19 14:00:12 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <functional>
#include <iostream>
#define BLACK	0
#define RED		1
#define RESET   "\033[0m"
#define BLACKK   "\033[1m\033[30m"      /* Black */
#define REDD     "\033[31m"      /* Red */

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
class redBlackTree
{
	class node;
	typedef T													value_type;
	// typedef typename value_type::first_type					first_type;
	// typedef typename value_type::second_type					second_type;
	typedef Compare												key_compare;
	typedef typename redBlackTree<T>::node::pointer				node_ptr;
	// ? https://stackoverflow.com/questions/14148756/what-does-template-rebind-do
	typedef	typename Alloc::template rebind<node>::other		alloc_type;
	
	public:
		
		redBlackTree(void) : _less(), _alloc(), _root(NULL), _nil(_root)  {}
		~redBlackTree(void) {}
		// * Print constructed binary tree
		struct Trunk
		{
			Trunk *prev;
			std::string str;
		
			Trunk(Trunk *prev, std::string str)
			{
				this->prev = prev;
				this->str = str;
			}
		};
		
		// Helper function to print branches of the binary tree
		void showTrunks(Trunk *p)
		{
			if (p == nullptr) {
				return;
			}
		
			showTrunks(p->prev);
			std::cout << p->str;
		}
		
		void printTree(node_ptr root, Trunk *prev, bool isLeft)
		{
			if (root == nullptr) {
				return;
			}
		
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);
		
			printTree(root->right, trunk, true);
		
			if (!prev) {
				trunk->str = "———";
			}
			else if (isLeft)
			{
				trunk->str = ".———";
				prev_str = "   |";
			}
			else {
				trunk->str = "`———";
				prev->str = prev_str;
			}
		
			showTrunks(trunk);
			if (root->color == BLACK)
				std::cout  << BLACKK << " " << root->data << RESET << std::endl;
			else
				std::cout  << REDD << " " << root->data << RESET << std::endl;
		
			if (prev) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		
			printTree(root->left, trunk, false);
		} 
		
		node_ptr	search(node_ptr x, value_type key)
		{
			if (x == NULL || x->data == key) // (!_less(x->data, key) && !_less(key, x->data))) //x.data == key
				return x;
			if (_less(key, x->data))
				return search(x->left, key);
			else
				return search(x->right, key);
		}
	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
		void		inoderprint(node_ptr x)
		{
			if (x != NULL)
			{
				inoderprint(x->left);
				std::cout << "data : (" << x->data << "), ";
				std::cout << "left : (" << x->left << "), ";
				std::cout << "right : (" << x->right << "), ";
				std::cout << "parent(" << x->parent << "), ";
				std::cout << "\n";
				inoderprint(x->right);
				std::cout << "#############################\n";
			}
		}
		
		node_ptr	min(node_ptr x)
		{
			while (x->left != NULL)
				x = x->left;
			return x;
		}
		
		node_ptr	max(node_ptr x)
		{
			while (x->right != NULL)
				x = x->right;
			return x;
		}
		
		node_ptr	successor(node_ptr x)
		{
			node_ptr	y;
			
			if (x->right != NULL)
				return (min(x->right));
			y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		
		node_ptr	predecessor(node_ptr x)
		{
			node_ptr	y;
			
			if (x->left != NULL)
				return (max(x->left));
			y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		
		void			left_rotate(node_ptr x)
		{
			node_ptr	y;

			//* set y
			y = x->right;
			//* turn y’s left subtree into x’s right subtree
			// printTree(_root, nullptr, false);
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			//* link x’s parent to y
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				this->_root = y;
				// _nil.left = root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			//* put x on y’s left
			y->left = x;
			x->parent = y;
		}
		
		void			right_rotate(node_ptr x)
		{
			node_ptr	y;
	
			y = x->left;
			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				this->_root = y;
				// _nil.left = root;
			}
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		
		node_ptr	create_node(value_type key, node_ptr parent)
		{
			node_ptr	new_node;
			
			new_node = _alloc.allocate(1);
			// _alloc.construct(new_node, node(key, NULL, parent));
			_alloc.construct(new_node, key);
			new_node->parent = parent;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->color = RED;
			new_node->data = key;
			return new_node;
		}
		
		node_ptr		bst_insert(value_type key)
		{
			/*node_ptr*/ node_ptr	x = _root;
			/*node_ptr*/ node_ptr	y = NULL;
			/*node_ptr*/ node_ptr	z = search(_root, key);
			/*node_ptr*/ node_ptr	parent;
			
			if (!z)
			{
				while (x != NULL)
				{
					y = x;
					if (key < x->data)
						x = x->left;
					else
						x = x->right;
				}
				z = create_node(key, y);
				if (y == NULL) //? should I : _nil.left = z ??
					_root = z;
				else if (key < y->data)
				{
					y->left = z;
					// z->is_left = true;
				}
				else
				{
					y->right = z;
					// z->is_left = false;
				}
			}
			else
				z->data = key;
			return z;
		}
		
		void		rb_insert(value_type key)
		{
			node_ptr k = bst_insert(key);
			
			if (!_root)
			{
				_root = k;
				// _nil.left = k;
			}
			while (k != _root && parent(k)->color == RED)
			{
				if (uncle(k) && uncle(k)->color == RED)
				{
					makeBlack(*parent(k));
					makeBlack(*uncle(k));
					if (grandParent(k) != _root)
						makeRed(*grandParent(k));
					k = grandParent(k);
				}
				else
				{
					if (parent(k) == grandParent(k)->right)
					{
						if (k == parent(k)->left)
						{
							// ? case 3.2.2 :: fist part
								k = k->parent;//parent(k);
								right_rotate(k);
						}
						// if (key == 87)
						// 	inoderprint(_root);
						// ? case 3.2.1 && second part of 3.2.2
						grandParent(k)->color = RED;
						parent(k)->color = BLACK;
						left_rotate(grandParent(k));
					}
					else
					{
						if (k == parent(k)->right)
						{
							// ? mirror case 3.2.2 :: fist part
							k = k->parent;
							left_rotate(k);
						}
						// ? mirror case 3.2.1 && second part of 3.2.2
						grandParent(k)->color = RED;
						parent(k)->color = BLACK;
						right_rotate(grandParent(k));
					}
				}
			}
			_root->color = BLACK;
			// inoderprint(_root);
		}
		
		// * on relie v au parent de v.
		void	rb_transplant(node_ptr u, node_ptr v)
		{
			if (!u->parent)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			if (v)
				v->parent = u->parent;
		}
//************************************************************************/
//* 																	  /
//*																		  /
//*								Deletion								  /
//*																		  /
//*																		  /
//************************************************************************/		
		void	rb_delete(value_type key)
		{
			node_ptr	z; // the node to be deleted
			node_ptr	y; // z's successor
			node_ptr	x; // x : y's child, which takes y's place in the tree.
						// x : keeps track of y's original position 
			bool		y_original_color;
			
			z = search(_root, key);
			if (!z)
				return ;
			y = z;
			y_original_color = y->color;
			if (!z->left)
			{
				x = y->right;
				rb_transplant(z, z->right); // replace z by its right child
			}
			else if (!z->right)
			{
				x = y->left;
				rb_transplant(z, z->left); // replace z by its left child
			}
			else
			{
				y = min(z->right); // y is the successor.
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					// swap y and its right so y become a leaf node
					// so it becomes easier to remove z.
					rb_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			// delete z;
			// printTree(_root, nullptr, false);
			// _alloc.destroy(z);
			// _alloc.deallocate(z, 1);
			// x = z;
			if (y_original_color == BLACK)
			{
				// fixDelete(x);
				// * RB-DELETE-FIXUP
					node_ptr	s;
					node_ptr	p;
				
					std::cout << REDD << y_original_color << " x = " << x->data << RESET << std::endl;
					while (x != _root && isBlack(x))// x->color == BLACK)
					{
				if (x)
					std::cout << REDD << x->data << RESET << std::endl;
						// p = parent(x);
				std::cout << REDD << parent(x)->data<< RESET << std::endl;
						if (x == parent(x)->left)
						{
							s = parent(x)->right;
							// case 3.1 
							if (isRED(s)) //s->color == RED)
							{
								s->color = BLACK;
								parent(x)->color = RED;
								left_rotate(p);
								// p = parent(x);
							}
							// case 3.2
							if (isBlack(s->left) && isBlack(s->right))//s->left == BLACK && s->right == BLACK)
							{
								s->color = RED;
								x = parent(x);
							}
							else if (isBlack(s->right)) //s->right == BLACK) // case 3.3 (s->left == RED & s->right = BLACK) & s is BLACK
							{
								s->color = RED;
								s->left->color = BLACK;
								right_rotate(s);
								// p = parent(x);
							}
							s->color = parent(x)->color;
							s->right->color = BLACK;
							p->color = BLACK;
							left_rotate(p);
							x = _root;
						}
						else
						{
							s = parent(x)->left;
							if (s->color == RED)
							{
								s->color = BLACK;
								parent(x)->color = RED;
								right_rotate(parent(x));
								s = parent(x)->left;
							}
				std::cout << REDD << s->data << RESET << std::endl;
							if (isBlack(s->right) && isBlack(s->left)) // s->right->color == BLACK && s->left->color == BLACK
							{
								s->color = RED;
								x = parent(x);
							}
							else if (isBlack(s->left)) //s->left->color == BLACK)
							{
								s->right->color = BLACK;
								s->color = RED;
								left_rotate(s);
								s = parent(x)->left;
							}
							s->color = parent(x)->color;
							parent(x)->color = BLACK;
							s->left->color = BLACK;
							right_rotate(parent(x));
							x = _root;
						}
						x->color = BLACK;
					}
				_alloc.destroy(z);
				_alloc.deallocate(z, 1);
			}
		}
	// private:
		key_compare		_less;
		alloc_type		_alloc;
		node_ptr		_root;
		node			_nil;
		bool			isBlack(node_ptr x) {return (!x || x->color == BLACK);}
		bool			isRED(node_ptr x) {if (!x) return false; return (x->color == RED);}
		void			makeBlack(node& x) {x.color = BLACK;}
		void			makeRed(node& x) {x.color = RED;}
		bool			isRoot(node_ptr x) {return (x == _root);}
		node_ptr		parent(node_ptr x) {return (x->parent);}
		node_ptr		sibling(node_ptr x)
		{
			if (x == parent(x)->left)
				return(parent(x)->right);
			else
				return(parent(x)->left);
		}
		node_ptr		grandParent(node_ptr x) {return(parent(parent(x)));}
		node_ptr		uncle(node_ptr x)
		{
			if (parent(x) == grandParent(x)->left)
				return grandParent(x)->right;
			return grandParent(x)->left;
		}

		private :
		struct node
		{
			typedef T						value_type;
			typedef node*					pointer;
			typedef const node*				const_pointer;
			typedef node&					reference;
			typedef const node&				const_reference;
			
			//* Data :
			value_type	data;
			pointer		parent;
			pointer		left;
			pointer		right;
			bool		color;
	
			// * Member functions : 
			node(pointer l) : data(), parent(NULL), left(l), right(NULL), color(BLACK) {}
			node(value_type d = value_type(), pointer p = NULL, pointer l = NULL, pointer r = NULL, bool cl = RED) : data(d), parent(p), left(l), right(r), color(cl) {}
			node(const_reference src) : data(src.data), parent(src.parent), left(src.left), right(src.right), color(src.color) {}
			reference operator=(const_reference src)
			{
				if (this == &src)
					return (*this);
				data = src.data;
				parent = src.parent;
				left = src.left;
				right = src.right;
				color = src.color;
				return (*this);
			}
			~node(void) {}
		};
};
