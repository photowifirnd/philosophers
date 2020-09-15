/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:34:30 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/15 14:39:46 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_time_in_ms(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000));
}

uint64_t	ft_time_in_micro_s(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000 * (uint64_t)1000) + (t.tv_usec));
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}
