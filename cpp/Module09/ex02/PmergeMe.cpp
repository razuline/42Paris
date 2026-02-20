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

/* --- Validation & Parsing --- */

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

/* --- Vector Algorithm Implementation --- */

// J(n) = J(n-1) + 2 * J(n-2)
void
PmergeMe::generateJacobsthalVector(std::vector<int> &jacob, int n)
{
	if (n <= 0)
		return;
	jacob.push_back(1);
	if (n == 1)
		return;
	jacob.push_back(3);
	while (jacob.back() < n)
	{
		int	next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
}

void
PmergeMe::sortVector()
{
	if (_vector.size() <= 1)
		return;

	std::vector<int>	mainChain;
	std::vector<int>	pend;
	int					straggler = -1;
	bool				hasStraggler = (_vector.size() % 2 != 0);

	// 1. Handle odd number of elements (straggler)
	if (hasStraggler)
	{
		straggler = _vector.back();
		_vector.pop_back();
	}

	// 2. Create pairs and separate larger elements into Main Chain
	for (size_t i = 0; i < _vector.size(); i += 2)
	{
		if (_vector[i] > _vector[i + 1])
		{
			mainChain.push_back(_vector[i]);
			pend.push_back(_vector[i + 1]);
		}
		else
		{
			mainChain.push_back(_vector[i + 1]);
			pend.push_back(_vector[i]);
		}
	}

	// 3. Sort the Main Chain (Recursive Ford-Johnson logic simplified)
	std::sort(mainChain.begin(), mainChain.end());

	// 4. Insertion Phase starting with the first element of pend
	mainChain.insert(mainChain.begin(), pend[0]);

	std::vector<int>	jacobSeq;
	generateJacobsthalVector(jacobSeq, pend.size());

	size_t				lastInserted = 1;
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		size_t	currIdx = std::min((size_t)jacobSeq[i], pend.size());
		// Insert elements backwards from the current Jacobsthal index
		for (size_t j = currIdx; j > lastInserted; j--)
		{
			int	val = pend[j - 1];
			// Binary search to find the correct insertion position
			std::vector<int>::iterator	pos =
					std::upper_bound(mainChain.begin(), mainChain.end(), val);
			mainChain.insert(pos, val);
		}
		lastInserted = std::max(lastInserted, currIdx);
	}

	// 5. Insert straggler if it exists
	if (hasStraggler)
	{
		std::vector<int>::iterator	pos = std::upper_bound(mainChain.begin(),
				mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}
	_vector = mainChain;
}

/* --- Deque Algorithm Implementation --- */

void
PmergeMe::generateJacobsthalDeque(std::deque<int> &jacob, int n)
{
	if (n <= 0)
		return;
	jacob.push_back(1);
	if (n == 1)
		return;
	jacob.push_back(3);
	while (jacob.back() < n)
	{
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
	}
}

void
PmergeMe::sortDeque()
{
	if (_deque.size() <= 1)
		return;

	std::deque<int>	mainChain;
	std::deque<int>	pend;
	int				straggler = -1;
	bool			hasStraggler = (_deque.size() % 2 != 0);

	if (hasStraggler)
	{
		straggler = _deque.back();
		_deque.pop_back();
	}

	for (size_t i = 0; i < _deque.size(); i += 2)
	{
		if (_deque[i] > _deque[i + 1])
		{
			mainChain.push_back(_deque[i]);
			pend.push_back(_deque[i + 1]);
		}
		else
		{
			mainChain.push_back(_deque[i + 1]);
			pend.push_back(_deque[i]);
		}
	}

	std::sort(mainChain.begin(), mainChain.end());
	mainChain.push_front(pend[0]);

	std::deque<int>	jacobSeq;
	generateJacobsthalDeque(jacobSeq, pend.size());

	size_t			lastInserted = 1;
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		size_t	currIdx = std::min((size_t)jacobSeq[i], pend.size());
		for (size_t j = currIdx; j > lastInserted; j--)
		{
			int	val = pend[j - 1];
			std::deque<int>::iterator pos =
					std::upper_bound(mainChain.begin(), mainChain.end(), val);
			mainChain.insert(pos, val);
		}
		lastInserted = std::max(lastInserted, currIdx);
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator	pos = std::upper_bound(mainChain.begin(),
				mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}
	_deque = mainChain;
}

/* ------------------------------ CORE METHODS ------------------------------ */

/* --- Execution & Display --- */

void
PmergeMe::run(int ac, char **av)
{
	struct timeval	start, end;

	// 1. Measure and sort Vector
	gettimeofday(&start, NULL);
	for (int i = 1; i < ac; i++)
	{
		if (!isValidInput(av[i]))
			throw std::runtime_error("Error");
		_vector.push_back(std::atoi(av[i]));
	}
	sortVector();
	gettimeofday(&end, NULL);
	_vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 +
			(end.tv_usec - start.tv_usec);

	// 2. Measure and sort Deque
	gettimeofday(&start, NULL);
	for (int i = 1; i < ac; i++)
	{
		_deque.push_back(std::atoi(av[i]));
	}
	sortDeque();
	gettimeofday(&end, NULL);
	_dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 +
			(end.tv_usec - start.tv_usec);
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
