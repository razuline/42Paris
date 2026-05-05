/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 21:07:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "searchable_bag.hpp"

class set
{
private:
	searchable_bag	*_bag; // Pointer to the bag inside

public:
	/* --- Orthodox Canonical Form --- */
	set(searchable_bag &bag);
	set(const set &copy);
	set	&operator=(const set &other);
	~set();

	/* --- Core Methods --- */
	void	insert(int value);
	void	insert(int *array, int size);
	bool	has(int value) const;
	void	print() const;
	void	clear();

	/* --- Getter --- */
	searchable_bag	&get_bag() const; // Returns the bag reference
};

#endif