#include "philo.h"

void	ft_get_sleep(t_philo *ph)
{
	ft_messages(ph, "philosopher is sleeping\n", 0);
	usleep(ph->r->tt_sleep);
}

void	ft_get_lunch(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex);
	ph->cnt++;
	ph->eat_flag = 1;
	ph->will_die = ft_time_in_micro_s() + ph->r->tt_die;
	ph->last_eat = ph->will_die - ph->r->tt_die;
	usleep(ph->r->tt_eat);
	pthread_mutex_unlock(&ph->r->forks[ph->r_hand]);
	pthread_mutex_unlock(&ph->r->forks[ph->l_hand]);
	ph->eat_flag = 0;
	ft_messages(ph, "philosopher has eaten\n", 0);
	pthread_mutex_unlock(&ph->mutex);
	pthread_mutex_lock(&ph->r->fork_state);
	ph->r->n_forks[ph->l_hand] = 0;
	ph->r->n_forks[ph->r_hand] = 0;
	pthread_mutex_unlock(&ph->r->fork_state);
	pthread_mutex_unlock(&ph->eat);
	/*Bloquea y desbloquea para coger 2 tenedores a la vez*/
}

void	ft_get_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ft_messages(ph, "philosopher has taken a left fork\n", 0);
	pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
	ft_messages(ph, "philosopher has taken a right fork\n", 0);
}

void	ft_get_forks_reverse(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
	ft_messages(ph, "philosopher has taken a right fork\n", 0);
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ft_messages(ph, "philosopher has taken a left fork\n", 0);
}

int	ft_can_take(t_philo *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->r->fork_state);
	if (ph->r->n_forks[ph->l_hand] == 0 && ph->r->n_forks[ph->r_hand] == 0)
	{
		ph->r->n_forks[ph->l_hand] = 1;
		ph->r->n_forks[ph->r_hand] = 1;
		if (ph->id % 2)
			ft_get_forks(ph);
		else
			ft_get_forks_reverse(ph);
		ret = 1;
	}
	pthread_mutex_unlock(&ph->r->fork_state);
	//Recuerda que si te quedas con este mutex, debes destruirlo desde ft_finish
	return (ret);
}

void	ft_living(void *ph)
{
	t_philo		*philo;
	pthread_t	pthread_id;
	int		must_continue;

	must_continue = 1;
	philo = (t_philo *)ph;
	philo->will_die = ft_time_in_micro_s() + philo->r->tt_die;
	philo->last_eat = philo->will_die - philo->r->tt_die;
	if (pthread_create(&pthread_id, NULL, (void *)ft_eat_or_die, philo) != 0)
		must_continue = 0;
	pthread_detach(pthread_id);
	while (must_continue && !philo->r->is_dead)
	{
		if (ft_can_take(ph))
		{
			ft_get_lunch(philo);
			ft_get_sleep(philo);
			ft_messages(philo, "philosopher is thinking\n", 0);
		}
		usleep(73);
	}
}
