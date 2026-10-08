#include <iostream>

int main()
{
    char unit;
    double temp;
    if (!(std::cin >> unit >> temp))
    {
        std::cout << "Invalid input\n";
        return 0;
    }
    if (unit == 'C')
    {
        std::cout << temp * 9 / 5 + 32 << " F\n";
    }
    else if (unit == 'F')
    {
        std::cout << (temp - 32) * 5 / 9 << " C\n";
    }
    else
    {
        std::cout << "Invalid input\n";
    }
}
