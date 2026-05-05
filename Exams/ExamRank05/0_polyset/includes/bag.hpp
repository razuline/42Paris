/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bag.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:12:08 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 20:55:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAM_ASSIGNMENTS_BAG_HPP
# define EXAM_ASSIGNMENTS_BAG_HPP

class bag
{
public:
	/* --- Core Methods --- */
	virtual void	insert(int) = 0;
	virtual void	insert(int *, int) = 0;
	virtual void	print() const = 0;
	virtual void	clear() = 0;
};

#endif