/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:24:19 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/10 14:26:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

void	push(t_stack **src, t_stack **dst)
{
	t_stack	*tmp;

	if (!*src)
		return ;

	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dst;
	*dst = tmp;
}
