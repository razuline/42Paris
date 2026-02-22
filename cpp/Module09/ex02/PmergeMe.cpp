/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:39:41 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/20 20:19:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

PmergeMe::PmergeMe() :
	_vectorTime(0), _dequeTime(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;

	// std::cout << "Copy constructor called" << std::endl;
}

PmergeMe
&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
		_vectorTime = other._vectorTime;
		_dequeTime = other._dequeTime;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

PmergeMe::~PmergeMe()
{
	// std::cout << "Destructor called" << std::endl;
}

/* --------------------------- INTERNAL FUNCTIONS --------------------------- */

// Checks if the input string consists only of digits
bool
PmergeMe::isValidInput(const std::string &str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

// Generates Jacobsthal numbers (1, 3, 5, 11, 21...) for groups
// J(n) = J(n-1) + 2 * J(n-2)
std::vector<size_t>
PmergeMe::generateJacobsthal(size_t n)
{
	std::vector<size_t>	jacob;

	if (n == 0)
		return jacob;

	jacob.push_back(1);
	if (n == 1)
		return jacob;

	jacob.push_back(3);

	while (jacob.back() < n)
	{
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
	}
	return jacob;
}

/* --- Vector Algorithm Implementation --- */

// The core Ford-Johnson (Merge-Insertion) algorithm
std::vector<int>
PmergeMe::fordJohnsonVector(std::vector<int> &cont)
{
	if (cont.size() <= 1)
		return cont;

	// 1. Handle odd number of elements (straggler)
	int		straggler = -1;
	bool	hasStraggler = cont.size() % 2 != 0;

	if (hasStraggler)
	{
		straggler = cont.back();
		cont.pop_back();
	}

	// 2. Create pairs and sort each pair (larger element first)
	std::vector<std::pair<int, int> >	pairs;

	for (size_t i = 0; i < cont.size(); i += 2)
	{
		if (cont[i] < cont[i + 1])
			pairs.push_back(std::make_pair(cont[i + 1], cont[i]));
		else
			pairs.push_back(std::make_pair(cont[i], cont[i + 1]));
	}

	// 3. Recursively sort the larger elements (the "winners")
	std::vector<int>	winners;

	for (size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	winners = fordJohnsonVector(winners);

	// 4. Build Main Chain and Pend sequence based on sorted winners
	std::vector<int>	mainChain = winners;
	std::vector<int>	pend;

	for (size_t i = 0; i < mainChain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (mainChain[i] == pairs[j].first)
			{
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}

	// 5. Insert the first element of pend into mainChain (free comparison)
	mainChain.insert(mainChain.begin(), pend[0]);

	// 6. Strategic insertion using Jacobsthal groups
	std::vector<size_t>	jacob = generateJacobsthal(pend.size());
	size_t				lastInserted = 1;

	for (size_t i = 0; i < jacob.size(); i++)
	{
		size_t	curr = std::min(jacob[i], (size_t)pend.size());

		// Insert elements backwards from the current Jacobsthal index
		for (size_t j = curr; j > lastInserted; j--)
		{
			std::vector<int>::iterator	pos
					= std::lower_bound(mainChain.begin(), mainChain.end(),
						pend[j - 1]);
			mainChain.insert(pos, pend[j - 1]);
		}
		lastInserted = std::max(lastInserted, curr);
	}

	// 7. Finally insert the straggler if it exists
	if (hasStraggler)
	{
		std::vector<int>::iterator	pos
				= std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}
	return mainChain;
}

/* --- Deque Algorithm Implementation --- */

std::deque<int>
PmergeMe::fordJohnsonDeque(std::deque<int> &cont)
{
	if (cont.size() <= 1)
		return cont;

	int		straggler = -1;
	bool	hasStraggler = cont.size() % 2 != 0;

	if (hasStraggler)
	{
		straggler = cont.back();
		cont.pop_back();
	}

	std::deque<std::pair<int, int> >	pairs;

	for (size_t i = 0; i < cont.size(); i += 2)
	{
		if (cont[i] < cont[i + 1])
			pairs.push_back(std::make_pair(cont[i + 1], cont[i]));
		else
			pairs.push_back(std::make_pair(cont[i], cont[i + 1]));
	}

	std::deque<int>	winners;

	for (size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	winners = fordJohnsonDeque(winners);

	std::deque<int>	mainChain = winners;
	std::deque<int>	pend;

	for (size_t i = 0; i < mainChain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (mainChain[i] == pairs[j].first)
			{
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}
	mainChain.push_front(pend[0]);

	std::vector<size_t>	jacob = generateJacobsthal(pend.size());
	size_t				lastInserted = 1;

	for (size_t i = 0; i < jacob.size(); i++)
	{
		size_t	curr = std::min(jacob[i], (size_t)pend.size());

		for (size_t j = curr; j > lastInserted; j--)
		{
			std::deque<int>::iterator	pos
					= std::lower_bound(mainChain.begin(), mainChain.end(),
						pend[j - 1]);
			mainChain.insert(pos, pend[j - 1]);
		}
		lastInserted = std::max(lastInserted, curr);
	}
	if (hasStraggler)
	{
		std::deque<int>::iterator	pos
				= std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}
	return mainChain;
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
PmergeMe::run(int ac, char **av)
{
	struct timeval	start, end;

	// Process and time the Vector container
	gettimeofday(&start, NULL);

	for (int i = 1; i < ac; i++)
	{
		if (!isValidInput(av[i]))
			throw std::runtime_error("Error");
		_vector.push_back(std::atoi(av[i]));
	}
	_vector = fordJohnsonVector(_vector);

	gettimeofday(&end, NULL);
	_vectorTime = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);

	// Process and time the Deque container
	gettimeofday(&start, NULL);

	for (int i = 1; i < ac; i++)
		_deque.push_back(std::atoi(av[i]));
	_deque = fordJohnsonDeque(_deque);

	gettimeofday(&end, NULL);
	_dequeTime = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
}

void
PmergeMe::printBefore(int ac, char **av) const
{
	std::cout << "Before: ";

	for (int i = 1; i < ac; i++)
		std::cout << av[i] << " ";
	std::cout << std::endl;
}

void
PmergeMe::printAfter() const
{
	std::cout << "After:  ";

	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}

void
PmergeMe::printTime() const
{
	std::cout << "Time to process a range of " << _vector.size()
			  << " elements with std::vector : " << _vectorTime
			  << " us" << std::endl;

	std::cout << "Time to process a range of " << _deque.size()
			  << " elements with std::deque  : " << _dequeTime
			  << " us" << std::endl;
}
