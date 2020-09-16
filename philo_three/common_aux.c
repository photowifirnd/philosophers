/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:30:35 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:32:41 by jheras-f         ###   ########.fr       */
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

void		ft_putnbr(long long int n)
{
	unsigned long long int	num;

	if (n < 0)
	{
		num = n * -1;
		ft_putchar('-');
	}
	else
		num = n;
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
		ft_putchar((num + '0'));
}
