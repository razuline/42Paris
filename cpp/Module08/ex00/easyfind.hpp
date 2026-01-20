/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:51:13 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 12:54:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm> // std::find(first, last, value)
# include <exception>
# include <iostream>

/* ------------------------- CUSTOM EXCEPTION CLASS ------------------------- */

class NoOccurenceException : public std::exception
{
public:
	virtual const char	*what() const throw()
	{
		return "Error: No occurrence is found in the container!";
	}
};

/* ---------------------------- FUNCTION TEMPLATE --------------------------- */

template <typename T>
typename T::iterator	easyfind(T &container, int value)
{
	typename T::iterator
	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
	{
		throw NoOccurenceException();
	}
	return it;
}

#endif