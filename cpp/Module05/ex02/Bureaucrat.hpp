/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:18 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 18:28:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <exception>
# include <iostream>
# include <string>

class AForm;

class Bureaucrat
{
private:
	const std::string	_name;
	unsigned int		_grade; // Grade from 1 (high) to 150 (low)

public:
	Bureaucrat(std::string name, int grade);
	Bureaucrat(const Bureaucrat &copy);
	Bureaucrat &operator=(const Bureaucrat &other);
	~Bureaucrat();

	// --- Getters ---
	const std::string	getName() const;
	unsigned int		getGrade() const;

	// --- Member Functions ---
	void	incrementGrade();
	void	decrementGrade();
	void	signForm(AForm &f);

	// --- Custom Exceptions ---
	// Inherit from std::exception to be catchable
	class GradeTooHighException : public std::exception
	{
	public:
		// virtual what() returns the error message
		virtual const char	*what() const throw()
		{
			return "Grade is too high (must be >= 1)";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char	*what() const throw()
		{
			return "Grade is too low (must be <= 150)";
		}
	};
};

// Operator overload for printing the bureaucrat
std::ostream	&operator<<(std::ostream &out, const Bureaucrat &b);

#endif