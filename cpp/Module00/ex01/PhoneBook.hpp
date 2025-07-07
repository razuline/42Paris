/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:10:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/07 16:21:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iomanip>
# include <iostream>
# include <string>
# include "Contact.hpp"

class PhoneBook {
	private:
		Contact 	_contacts[8];
		int			_index;

	public:
		PhoneBook(void);
		void	addContact();
		void	searchContact();
};

#endif
