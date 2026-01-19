#include "Array.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

#define MAX_VAL 750

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	// 1. Creation of the array and mirror for verification
	Array<int>	numbers(MAX_VAL);
	int			*mirror = new int[MAX_VAL];

	srand(time(NULL));

	// 2. Filling arrays with random values
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int	value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}

	/* --- Scope --- */
	// 3. Testing Deep Copy and Scope
	{
		std::cout << "Testing assignment operator and copy constructor..."
				  << std::endl;
		Array<int>	tmp = numbers;
		Array<int>	test(tmp);
		// tmp and test will be destroyed here, checking for double-free
	}

	// 4. Verification that values are identical
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "Error: didn't save the same value!" << std::endl;
			return 1;
		}
	}
	std::cout << "Values verification: OK!" << std::endl;

	// 5. Testing Exception handling (Out of bounds)
	std::cout << "Testing out of bounds (negative index):" << std::endl;
	try
	{
		numbers[-2] = 0;
	}
	catch(const std::exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
	}
	std::cout << "Testing out of bounds (index too high):" << std::endl;
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
	}

	// 6. Final Stress Test for Deep Copy
	// Fills the original 'numbers' array with new random values.
	// If deep copy was not implemented correctly,
	// this loop would cause a crash (segmentation fault).
	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}

	// 7. Cleanup
	delete[] mirror;
	std::cout << "End of tests. Everything is fine!" << std::endl;

	return 0;
}
