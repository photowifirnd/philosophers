/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:34:46 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:52:47 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_even(t_rules *r)
{
	t_philo		*philo;
	size_t		i;

	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 0)
		{
			philo = (&r->philo[i]);
			if ((philo->pid = fork()) < 0)
				return (1);
			if (philo->pid == 0)
			{
				ft_living(philo);
				printf("Saliendo: \n");
				exit(0);
			}
		}
		i++;
	}
	usleep(200);
	return (0);
}
