/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:21:06 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:31:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class Brain
{
private:
	// This is the data we need to protect and copy correctly.
	std::string	_ideas[100];

public:
	Brain(void);
	Brain(const Brain &copy);
	Brain &operator=(const Brain &other);
	~Brain(void);

	// --- Getters ---
	std::string getIdea(int idx) const;
	
	// --- Setters ---
	void setIdea(int idx, const std::string &idea);
};

#endif