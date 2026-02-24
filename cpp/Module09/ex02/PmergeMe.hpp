/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:39:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/20 20:24:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <algorithm>
# include <sys/time.h>
# include <cstdlib>

class PmergeMe
{
private:
	// Containers for the two required implementations
	std::vector<int>	_vector;
	std::deque<int>		_deque;
	// Time tracking variables
	double	_vectorTime;
	double	_dequeTime;

	/* --- Common Logic (Internal) --- */
	// Validation
	bool				isValidInput(const std::string &str);

	// Algorithm Vector
	std::vector<int>	fordJohnsonVector(std::vector<int> &cont);

	// Algorithm Deque
	std::deque<int>		fordJohnsonDeque(std::deque<int> &cont);

	// Tools
	std::vector<size_t>	generateJacobsthal(size_t n);

public:
	/* --- Orthodox Canonical Form --- */
	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe	&operator=(const PmergeMe &other);
	~PmergeMe();

	/* --- Core Methods --- */
	// Parse the arguments and launch the sorting process
	void	run(int ac, char **av);

	// Display functions
	void	printBefore(int ac, char **av) const;
	void	printAfter() const;
	void	printTime() const;
};

#endif