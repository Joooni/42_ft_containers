#include "../RBT.hpp"
#include <functional>
#include <time.h>
#include <stdlib.h>
#include "../vector.hpp"
#define DELIM	std::string(10, '~')
int main(void)
{

	std::cout << DELIM << "Test 1" << DELIM << std::endl;
	{
		ft::RBT<int, std::less<int> > RBTorsten;
		for (int i = 1; i < 25; i++)
			RBTorsten.insert(i);
		RBTorsten.printTree();
	}
	// std::cout << DELIM << "Test 2" << DELIM << std::endl;
	// {
	// 	ft::RBT<int, std::less<int> >	RBTommy;
	// 	srand(time(NULL));
	// 	for (int i = 0; i < 20; i++)
	// 	{
	// 		int nbr = rand() % 47;
	// 		std::cout << nbr <<std::endl;
	// 		RBTommy.insert(nbr);
	// 	}
	// 	RBTommy.printTree();
	// }
}
