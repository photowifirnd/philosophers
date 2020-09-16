/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 08:42:24 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:05:39 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_counter(t_rules *r)
{
	pthread_t	thread_id;

	if (r->n_times_to_eat > 0)
	{
		if (pthread_create(&thread_id, NULL,
					(void *)ft_count_eaters, (void *)r) != 0)
			return (1);
		pthread_detach(thread_id);
	}
	return (0);
}

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
			if (pthread_create(&thread_id, NULL,
						(void *)ft_living, philo) != 0)
				return (1);
			pthread_detach(thread_id);
		}
		i++;
	}
	usleep(200);
	return (0);
}
