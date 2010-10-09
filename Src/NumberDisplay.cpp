#include <iostream>
#include "NumberDisplay.hpp"

void CNumberDisplay::SetNumber(int Number)
{
	std::cout << "Number: " << Number << std::endl;
}

void CNumberDisplay::SetScreenPosition(int x, int y)
{
	std::cout << "Position: " << x << ", " << y << std::endl;
}
