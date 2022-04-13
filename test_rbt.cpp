
#include "rbt.hpp"
#include "utility/utility.hpp"
// #define RESET   "\033[0m"
// #define BLACKK   "\033[36m"      /* Black */
// #define REDD     "\033[31m"      /* Red */

template<typename T>
void	print_number(T n, bool cl)
{
	if (cl)
		std::cout << REDD << n << RESET << std::endl;
	else
		std::cout << BLACKK << n << RESET << std::endl;
}

int main()
{
	redBlackTree<int> test;

	test.rb_insert(61);
	test.rb_insert(85);
	test.rb_insert(52);
	test.rb_insert(93);
	test.rb_insert(100);
	// test.rb_insert(87);

	// print_number(test._root->data, test._root->color);
	// print_number(test._root->left->data, test._root->left->color);
	// std::cout <<  test._root->left->left << " " << test._root->left->right << std::endl;
	// print_number(test._root->right->data, test._root->right->color);
	// print_number(test._root->right->left->data, test._root->right->left->color);
	// std::cout <<  test._root->right->left->left << " " << test._root->right->left->right << std::endl;
	// print_number(test._root->right->right->data, test._root->right->right->color);
	// std::cout <<  test._root->right->right->left << " " << test._root->right->right->right << std::endl;
	test.printTree(test._root, nullptr, false);
	return 0;
}