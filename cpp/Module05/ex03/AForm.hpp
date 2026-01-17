/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:50 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:23:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class AForm
{
private:
	const std::string	_name;
	bool				_isSigned;
	const unsigned int	_gradeToSign;
	const unsigned int	_gradeToExec;

public:
	// --- Orthodox Canonical Form ---
	AForm(std::string name, int gradeToSign, int gradeToExec);
	AForm(const AForm &src);
	AForm &operator=(const AForm &other);
	// Virtual destructor is mandatory for base classes to ensure
	// proper cleanup of derived objects.
	virtual ~AForm();

	// --- Getters ---
	const std::string	getName() const;
	bool				getIsSigned() const;
	unsigned int		getGradeToSign() const;
	unsigned int		getGradeToExec() const;

	// --- Member Functions ---
	// Changes the form status to signed if bureaucrat's grade is high enough
	void	beSigned(const Bureaucrat &b);

	// Pure virtual function: makes this class abstract.
	// Every derived class MUST implement its own version of execute.
	virtual void	execute(Bureaucrat const &executor) const = 0;

	// Helper function to check if the form can be executed.
	// Requirements: form must be signed AND executor grade must be high enough.
	void	checkExecutability(Bureaucrat const &executor) const;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual const char	*what() const throw()
		{
			return "Form is not signed yet!";
		}
	};
};

// Operator overload for printing Form information
std::ostream	&operator<<(std::ostream &out, const AForm &b);

#endif