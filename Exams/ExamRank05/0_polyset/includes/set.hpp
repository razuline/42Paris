/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/10 18:56:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "searchable_bag.hpp"

class set
{
private:
	searchable_bag	*_bag; // Internal pointer to a searchable data structure

public:
	/* --- Orthodox Canonical Form --- */
	set(searchable_bag &bag);
	set(const set &copy);
	set	&operator=(const set &other);
	~set();

	/* --- Core Methods --- */
	// Logic: only call bag->insert() if bag->has() returns false
	void			insert(int value);
	void			insert(int *array, int size);

	bool			has(int value) const;
	void			print() const;
	void			clear();

	/* --- Getter --- */
	searchable_bag	&get_bag() const; // Access the internal bag
};

#endif