/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:34:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/02 15:36:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef TEST

# include "../includes/philo.h"

u_int64_t	get_time(void);
void		ft_sleep(u_int64_t ms);

int	main(void)
{
	u_int64_t	start;

	start = get_time();
	ft_sleep(1000);
	printf("Slept for %llu ms\n", get_time() - start);
	return (0);
}

#endif