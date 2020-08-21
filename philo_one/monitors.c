/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:54:20 by jheras-f          #+#    #+#             */
/*   Updated: 2020/08/21 10:00:41 by jheras-f         ###   ########.fr       */
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
			pthread_mutex_lock(&r->philo[j++].eat);
		i++;
	}
	if (r->n_times_to_eat > 0)
		r->is_dead = 1;
	pthread_mutex_unlock(&r->philo_dead);
}

void	ft_eat_or_die(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		if (philo->r->is_dead)
			return ;
		pthread_mutex_lock(&philo->mutex);
		if (!philo->eat_flag && ft_time_in_ms() > philo->will_die / 1000)
		{
			ft_messages(philo, "philosofer died\n", 1);
			pthread_mutex_lock(&philo->r->message);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->r->philo_dead);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(2000);
	}
}
