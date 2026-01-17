/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:30:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:17:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include "AForm.hpp"

# include <cstdlib>
# include <exception>
# include <iostream>
# include <string>

class RobotomyRequestForm : public AForm
{
private:
	const std::string	_target;

public:
	// --- Orthodox Canonical Form ---
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &src);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	~RobotomyRequestForm();

	// --- Member Functions ---
	virtual void	execute(Bureaucrat const &executor) const;
};

#endif