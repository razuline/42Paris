/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:13:42 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/21 19:18:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

RPN::RPN()
{
	//std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN &copy)
{
	*this = copy;

	//std::cout << "Copy constructor called" << std::endl;
}

RPN
&RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

RPN::~RPN()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- INTERNAL FUNCTIONS --------------------------- */

bool
RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

int
RPN::performOperation(int a, int b, char op) const
{
	if (op == '+')
		return a + b;
	if (op == '-')
		return a - b;
	if (op == '*')
		return a * b;
	if (op == '/')
	{
		if (b == 0)
			throw std::runtime_error("Error");
		return a / b;
	}
	return 0;
}

/* -------------------------------- METHODS --------------------------------- */

void
RPN::calculate(const std::string &expression)
{
	for (size_t i = 0; i < expression.length(); ++i)
	{
		char	c = expression[i];

		// Skip spaces
		if (c == ' ')
			continue;
		// 1. If it's a digit (0-9)
		if (std::isdigit(c))
		{
			// Check if the next character is also a digit
			if (i + 1 < expression.length() && std::isdigit(expression[i + 1]))
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			// Convert char to int and push
			_stack.push(c - '0');
		}
		// 2. If it's an operator
		else if (isOperator(c))
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			// Pop the two top values
			// Order is important: the first pop is 'b', the second is 'a'
			int	b = _stack.top();
			_stack.pop();
			int	a = _stack.top();
			_stack.pop();

			try
			{
				_stack.push(performOperation(a, b, c));
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				return;
			}
		}
		else
		{
			// Invalid characters or brackets
			std::cerr << "Error" << std::endl;
			return;
		}
	}
	// 3. Final check: only one value should remain
	if (_stack.size() != 1)
		std::cerr << "Error" << std::endl;
	else
		std::cout << _stack.top() << std::endl;
}
