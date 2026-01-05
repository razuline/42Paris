/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:50 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/05 17:32:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <exception>
# include <iostream>
# include <string>

// Forward declaration to avoid circular dependencies
class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	bool				_isSigned;
	const unsigned int	_gradeToSign;
	const unsigned int	_gradeToExec;

public:
	// --- Orthodox Canonical Form ---
	Form(std::string name, int gradeToSign, int gradeToExec);
	Form(const Form &src);
	Form &operator=(const Form &other);
	~Form();
	
	// --- Getters ---
	const std::string	getName() const;
	bool				getIsSigned() const;
	unsigned int		getGradeToSign() const;
	unsigned int		getGradeToExec() const;

	// --- Member Functions ---
	void	beSigned(const Bureaucrat &b);

	// --- Custom Exceptions ---
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char	*what() const throw()
		{
			return "Form grade is too high!";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char	*what() const throw()
		{
			return "Form grade is too low!";
		}
	};
};

// Operator overload for printing Form information
std::ostream	&operator<<(std::ostream &out, const Form &b);

#endif