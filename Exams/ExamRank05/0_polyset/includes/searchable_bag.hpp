/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_bag.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:23:19 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 20:29:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAM_ASSIGNMENTS_SORTABLE_HPP
# define EXAM_ASSIGNMENTS_SORTABLE_HPP

# include "bag.hpp"

class searchable_bag :
	virtual public bag
{
public:
	/* --- Core Methods --- */
	virtual bool	has(int) const = 0;
};

#endif