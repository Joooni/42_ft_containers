#include "../RBT.hpp"
#include <functional>

int main(void)
{
	ft::RBT<int, std::less<int> > RBTorsten;
	for (int i = 1; i < 20; i++)
		RBTorsten.insert(i);
}