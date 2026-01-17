/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:40:09 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:59:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <string>

// A simple structure representing our data.
// It must be non-empty to satisfy the subject requirements.
struct Data
{
	int			id;
	std::string	name;
	std::string	value;
};

#endif