/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:14:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 18:20:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>

class RPN
{
private:
	// Usage of std::stack as the container
	std::stack<int>	_stack;

public:
	/* --- Orthodox Canonical Form --- */
	RPN();
	RPN(const RPN &copy);
	RPN	&operator=(const RPN &other);
	~RPN();

	/* --- Methods --- */
	void	calculate(const std::string &expression);
};

#endif