/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:35:11 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 14:17:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"

# include <iostream>
# include <string>

class Intern
{
public:
	// --- Orthodox Canonical Form ---
	Intern();
	Intern(const Intern &src);
	Intern &operator=(const Intern &other);
	~Intern();

	// --- Member Functions ---
	// Creates a form based on the string name.
	// Returns a pointer to AForm, or NULL if the form name is unknown.
	AForm			*makeForm(std::string name, std::string target);

private:
	// Helper methods for form creation to avoid long if/else chains.
	static AForm	*createShrubbery(std::string target);
	static AForm	*createRobotomy(std::string target);
	static AForm	*createPardon(std::string target);
};

#endif