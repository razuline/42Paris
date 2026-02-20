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
# include <ctime>
# include <algorithm>
# include <sys/time.h>

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
	// Helper to check if the input is a valid positive integer
	bool	isValidInput(const std::string &str);

	/* --- Vector Algorithm Implementation --- */
	void	sortVector();
	void	generateJacobsthalVector(std::vector<int> &jacob, int n);

	/* --- Deque Algorithm Implementation --- */
	void	sortDeque();
	void	generateJacobsthalDeque(std::deque<int> &jacob, int n);

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