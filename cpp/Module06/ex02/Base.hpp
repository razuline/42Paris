/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:09:34 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 14:00:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>

// Base class with a mandatory virtual destructor.
// This makes the class polymorphic, allowing the use of dynamic_cast.
class Base
{
public:
	virtual ~Base();
};

#endif