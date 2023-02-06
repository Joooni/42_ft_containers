#include "../RBT.hpp"
#include <functional>

int main(void)
{
	ft::RBT<int, std::less<int> > RBTorsten;
	for (int i = 1; i < 25; i++)
	{
		std::cout << i << std::endl;
		RBTorsten.insert(i);
	}
	std::cout << RBTorsten.getRoot() << " root: " << *(RBTorsten.getRoot()->content) << std::endl;
	std::cout << RBTorsten.getRoot()->left_child << " root left: " << *(RBTorsten.getRoot()->left_child->content) << std::endl;
	std::cout << RBTorsten.getRoot()->right_child << " root right: " << *(RBTorsten.getRoot()->right_child->content) << std::endl;
	std::cout << RBTorsten.calculateHeight(RBTorsten.getRoot()) << std::endl;
	RBTorsten.printTree();
}
