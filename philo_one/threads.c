/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:44:41 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/15 14:51:44 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_even(t_rules *r)
{
	void		*philo;
	size_t		i;
	pthread_t	thread_id;

	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 0)
		{
			philo = (void *)(&r->philo[i]);
			if (pthread_create(&thread_id, NULL, (void *)ft_living, philo) != 0)
				return (1);
			pthread_detach(thread_id);
		}
		i++;
	}
	usleep(200);
	return (0);
}
