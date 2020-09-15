/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:41:14 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/15 15:07:27 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_finish(t_rules *r)
{
	size_t i;

	i = 0;
	while (i < r->n_philos)
	{
		if (r->forks != NULL)
			pthread_mutex_destroy(&r->forks[i]);
		pthread_mutex_destroy(&r->philo[i].mutex);
		pthread_mutex_destroy(&r->philo[i++].eat);
	}
	(r->forks != NULL) ? free(r->forks) : NULL;
	pthread_mutex_destroy(&r->philo_dead);
	pthread_mutex_destroy(&r->message);
	return (0);
}

int	ft_init_threads(t_rules *r)
{
	void		*philo;
	size_t		i;
	pthread_t	thread_id;

	if (r->n_times_to_eat > 0)
	{
		if (pthread_create(&thread_id, NULL,
				(void *)ft_count_eaters, (void *)r) != 0)
			return (1);
		pthread_detach(thread_id);
	}
	ft_init_even(r);
	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 1)
		{
			philo = (void *)(&r->philo[i]);
			if (pthread_create(&thread_id, NULL, (void *)ft_living, philo) != 0)
				return (1);
			pthread_detach(thread_id);
		}
		i++;
	}
	return (0);
}

int	ft_init(int argc, char *argv[], t_rules *r)
{
	return (ft_set_general(argc, argv, r)
		|| ft_set_philos(r)
		|| ft_set_forks(r));
}

int	main(int argc, char *argv[])
{
	t_rules	r;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Argument\n"));
	if (ft_init(argc, argv, &r))
		return (ft_error("Philo_one: error: bad arguments\n"));
	if (ft_init_threads(&r))
		return (1);
	pthread_mutex_lock(&r.philo_dead);
	pthread_mutex_unlock(&r.philo_dead);
	ft_finish(&r);
	return (0);
}
