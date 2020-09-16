/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_living.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:54:43 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:55:25 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_sleep(t_philo *ph)
{
	ft_messages(ph, "philosopher is sleeping\n", 0);
	usleep(ph->r->tt_sleep);
}

void	ft_get_lunch(t_philo *ph)
{
	sem_wait(ph->mutex);
	ph->eat_flag = 1;
	ph->will_die = ft_time_in_micro_s() + ph->r->tt_die;
	ft_messages(ph, "philosopher has eaten\n", 0);
	usleep(ph->r->tt_eat);
	ph->last_eat = ph->will_die - ph->r->tt_die;
	ph->eat_flag = 0;
	ft_leave_forks(ph);
	ph->cnt++;
	sem_post(ph->mutex);
	sem_post(ph->eat);
}

void	ft_get_forks(t_philo *ph)
{
	sem_wait(ph->r->forks);
	ft_messages(ph, "philosopher has taken a left fork\n", 0);
	sem_wait(ph->r->forks);
	ft_messages(ph, "philosopher has taken a right fork\n", 0);
}

void	ft_leave_forks(t_philo *ph)
{
	sem_post(ph->r->forks);
	sem_post(ph->r->forks);
}

void	ft_living(void *ph)
{
	t_philo		*philo;
	pthread_t	pthread_id;
	int			must_continue;

	must_continue = 1;
	philo = (t_philo *)ph;
	philo->will_die = ft_time_in_micro_s() + philo->r->tt_die;
	philo->last_eat = philo->will_die - philo->r->tt_die;
	if (pthread_create(&pthread_id, NULL, (void *)ft_eat_or_die, philo) != 0)
		must_continue = 0;
	pthread_detach(pthread_id);
	while (must_continue && !philo->r->is_dead)
	{
		ft_get_forks(philo);
		ft_get_lunch(philo);
		ft_get_sleep(philo);
		ft_messages(philo, "philosopher is thinking\n", 0);
	}
}
