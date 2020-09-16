/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:39:29 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:41:42 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_count_eaters(void *rules)
{
	t_rules	*r;
	size_t	i;
	size_t	j;

	r = (t_rules *)rules;
	i = 0;
	while (i < r->n_times_to_eat)
	{
		j = 0;
		while (j < r->n_philos)
			sem_wait(r->philo[j++].eat);
		i++;
	}
	if (r->n_times_to_eat > 0)
		r->is_dead = 1;
	sem_post(r->philo_dead);
}

void	ft_eat_or_die(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->eat_flag && ft_time_in_ms() > philo->will_die / 1000)
		{
			ft_messages(philo, "philosofer died\n", 1);
			sem_post(philo->mutex);
			sem_post(philo->r->philo_dead);
			return ;
		}
		sem_post(philo->mutex);
		usleep(10);
	}
}

int		ft_start_counting(t_rules *r)
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
