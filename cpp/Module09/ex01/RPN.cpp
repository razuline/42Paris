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

// Checks if the character is one of the four allowed operators
bool
RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

// Performs the calculation based on the operator token
int
RPN::applyOperation(int a, int b, char op)
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
			throw std::runtime_error("Error"); // Division by zero
		return a / b;
	}
	return 0;
}

/* -------------------------------- METHODS --------------------------------- */

void
RPN::calculate(const std::string &expr)
{
	for (size_t i = 0; i < expr.length(); ++i)
	{
		if (expr[i] == ' ')
			continue;

		// Each number must be a single digit < 10
		if (isdigit(expr[i]))
		{
			// Check if the next character is also a digit
			if (i + 1 < expr.length() && isdigit(expr[i + 1]))
			{
				std::cerr << "Error" << std::endl; // Invalid input
				return;
			}
			_stack.push(expr[i] - '0');
		}
		else if (isOperator(expr[i]))
		{
			// Need at least two operands
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			int	b = _stack.top();
			_stack.pop();
			int	a = _stack.top();
			_stack.pop();

			try
			{
				_stack.push(applyOperation(a, b, expr[i]));
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
		}
		else
		{
			std::cerr << "Error" << std::endl; // Invalid character
			return;
		}
	}

	// After processing, exactly one result must remain on the stack
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
	}
	else
	{
		std::cout << _stack.top() << std::endl;
	}
}
