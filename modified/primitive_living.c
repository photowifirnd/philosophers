#include "philo.h"

void	ft_get_sleep(t_philo *ph)
{
	ft_messages(ph, "philosopher is sleeping\n", 0);
	usleep(ph->r->tt_sleep);
}

void	ft_get_lunch(t_philo *ph)
{
	/* Start: Bloqueamos el código común a todos los filosofosll*/
	pthread_mutex_lock(&ph->mutex);

	/*Flag para indicar que el filosofo está comiendo*/
	ph->eat_flag = 1;

	/*Calculamos y establecemos los valores para el inicio de cada comida y cuando debe volver a comer*/
	ph->will_die = ft_time_in_micro_s() + ph->r->tt_die;
	/*end time: en micro segundos*/
	
	/*Tiempo que el filosofo emplea en comer*/
	usleep(ph->r->tt_eat);

	ph->last_eat = ph->will_die - ph->r->tt_die;
	ph->r->n_forks[ph->l_hand] = 0;
	ph->r->n_forks[ph->r_hand] = 0;
	
	/*Start: desbloqueo de los tenedores*/
	pthread_mutex_unlock(&ph->r->forks[ph->r_hand]);
	pthread_mutex_unlock(&ph->r->forks[ph->l_hand]);
	/*End del desbloqueo de los tenedores*/
	
	/* START: bloqueamos el codigo del estado de los tenedores comun a los filosofos*/
/*	pthread_mutex_lock(&ph->r->fork_state[ph->l_hand]);
	ph->r->n_forks[ph->l_hand] = 0;
	ph->r->n_forks[ph->r_hand] = 0;
	pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
*/	/* END: bloqueo estado tenedores. Referencia a ft_can_take*/
	/*Bloquea y desbloquea para coger 2 tenedores a la vez*/

	/*Flag para indicar que el filosofo ha terminado de comer*/
	ph->eat_flag = 0;
	
	/*Imprimimos un mensaje indicando el timestamp en milisegundos, id del filosofo y que ha comido*/
	ft_messages(ph, "philosopher has eaten\n", 0);

	/* END: desbloqueamos el codigo comun a todos los filosofos*/
	pthread_mutex_unlock(&ph->mutex);

	/* cnt es el contador usado cuando se le pasa el número de veces que cada filosofo debe comer */
	ph->cnt++;
	/* Desbloqueamos el codigo de conteo de comidas y el bucle contenido en el continua si procede*/
	pthread_mutex_unlock(&ph->eat);

}

void	ft_get_l_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ph->r->n_forks[ph->l_hand] = ph->id;
}

int	ft_get_r_fork(t_philo *ph)
{
	if (ph->r->n_forks[ph->l_hand] == ph->id && ph->r->n_forks[ph->r_hand] == 0)
	{
		pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
		ph->r->n_forks[ph->r_hand] = 1;
		ft_messages(ph, "philosopher has taken a left fork\n", 0);
		ft_messages(ph, "philosopher has taken a right fork\n", 0);
	}
	else if (ph->r->n_forks[ph->l_hand] == ph->id && ph->r->n_forks[ph->r_hand] == 1)
	{
		pthread_mutex_unlock(&ph->r->forks[ph->l_hand]);
		pthread_mutex_lock(&ph->r->fork_state[ph->l_hand]);
		ph->r->n_forks[ph->l_hand] = 0;
		pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
		return (1);
	}
	return (0);
}


/*int	ft_can_take(t_philo *ph)
{
	int	ret;

	ret = 0;
	if (ph->r->n_forks[ph->l_hand] == 0 && ph->r->n_forks[ph->r_hand] == 0)
	{
		pthread_mutex_lock(&ph->r->fork_state[ph->l_hand]);
		ph->r->n_forks[ph->l_hand] = 1;
		pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
		if (ph->r->n_forks[ph->r_hand] == 0)
		{
			pthread_mutex_lock(&ph->r->fork_state[ph->r_hand]);
			ph->r->n_forks[ph->r_hand] = 1;
			pthread_mutex_unlock(&ph->r->fork_state[ph->r_hand]);
		}
		else
		{
			pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
			pthread_mutex_lock(&ph->r->fork_state[ph->l_hand]);
			ph->r->n_forks[ph->l_hand] = 0;
			pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
			return (ret);
			
		}
		ret = 1;
	}
	//Recuerda que si te quedas con este mutex, debes destruirlo desde ft_finish
	return (ret);
}*/

void	ft_living(void *ph)
{
	t_philo		*philo;
	pthread_t	pthread_id;
	int		must_continue;
//	int		i;

	must_continue = 1;
	philo = (t_philo *)ph;
	philo->will_die = ft_time_in_micro_s() + philo->r->tt_die;
	philo->last_eat = philo->will_die - philo->r->tt_die;
	if (pthread_create(&pthread_id, NULL, (void *)ft_eat_or_die, philo) != 0)
		must_continue = 0;
	pthread_detach(pthread_id);
	while (must_continue && !philo->r->is_dead)
	{
		//pthread_mutex_lock(&philo->r->fork_state);
		//i = ft_can_take(philo);
		//pthread_mutex_unlock(&philo->r->fork_state);
		ft_get_l_fork(ph);
		if (ft_get_r_fork(ph) == 0)
		{
			ft_get_lunch(philo);
			ft_get_sleep(philo);
			ft_messages(philo, "philosopher is thinking\n", 0);
			usleep(3);
		}
		else
			usleep(philo->id + philo->r->n_philos);
	}
}
