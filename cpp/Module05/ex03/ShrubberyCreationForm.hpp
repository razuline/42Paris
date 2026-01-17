/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:29:18 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 19:02:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include "AForm.hpp"

# include <exception>
# include <fstream>
# include <iostream>
# include <string>

class ShrubberyCreationForm : public AForm
{
private:
	const std::string	_target;

public:
	// --- Orthodox Canonical Form ---
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &src);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
	~ShrubberyCreationForm();

	// --- Member Functions ---
	virtual void	execute(Bureaucrat const &executor) const;
};

#endif