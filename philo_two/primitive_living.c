/* Esta version trata de identificar el numero de philosophers que se le pasan por parametro, encaminando la ejecucion
 * de los hilos por un camino y otro en funcion de si el numero de philosophers totales es par o impar. a continuacion
 * ejecuta la accion de coger tenerodes dependiendo de si el propio philosopher está en una posición par o impar
 * ordenando coger los tenedores de dos en dos o en caso de ser par coger un tenedor y comprobar si el otro tenedor
 * está disponible o no y de no estarlo, volver a dejar el tenedor en la mesa para reintentarlo de nuevo más tarde.
 * VOY A REALIZAR UNA COMPIA DE ESTA VERSION PARA TRATAR DE LIMPIARLA. AYER PASÉ EL MINISHELL Y ESTAMOS A 11/09/2020
 * La version que estás editando pertenece al fichero philo_one_11_09_2020_mira_el_comentario_de_primitive.tar
 * en esta he borrado todo los comentarios y las rutas even y odd para verlo mas claro y tratar de dar solucion a los
 * filosofos.
 * */

#include "philo.h"

void	ft_get_sleep(t_philo *ph)
{
	ft_messages(ph, "philosopher is sleeping\n", 0);
	usleep(ph->r->tt_sleep);
}

void	ft_get_lunch(t_philo *ph)
{
	if (ph->cnt < (int)ph->r->n_times_to_eat || (int)ph->r->n_times_to_eat == 0)
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

/*void	ft_get_forks_odd(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
	ft_messages(ph, "philosopher has taken a right fork\n", 0);
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ft_messages(ph, "philosopher has taken a left fork\n", 0);
}


void	ft_get_l_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ph->r->n_forks[ph->l_hand] = ph->id;
}

int	ft_get_r_fork(t_philo *ph)
{
	if (ph->r->n_forks[ph->l_hand] == (int)ph->id && ph->r->n_forks[ph->r_hand] == -1)
	{
		pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
		ph->r->n_forks[ph->r_hand] = ph->id;
		ft_messages(ph, "philosopher has taken a left fork\n", 0);
		ft_messages(ph, "philosopher has taken a right fork\n", 0);
	}
	else if (ph->r->n_forks[ph->l_hand] == (int)ph->id && ph->r->n_forks[ph->r_hand] != -1)
	{
		pthread_mutex_unlock(&ph->r->forks[ph->l_hand]);
		pthread_mutex_lock(&ph->r->fork_state[ph->l_hand]);
		ph->r->n_forks[ph->l_hand] = -1;
		pthread_mutex_unlock(&ph->r->fork_state[ph->l_hand]);
		return (1);
	}
	return (0);
}*/

void	ft_option_a(t_philo *ph, int must)
{
	while (must && !ph->r->is_dead)
	{
		ft_get_forks(ph); //if get_fork fails, return ;
		ft_get_lunch(ph); //get lunch shoud be return a value en save it in shuld.end
		// Create a leave_forks function returning a value that is evaluated through an if condition
		// if (shuld_end) return; 
		ft_get_sleep(ph);
		ft_messages(ph, "philosopher is thinking\n", 0);
	}
}

/*void	ft_option_b(t_philo *ph, int must)
{
	while (must && !ph->r->is_dead)
	{
		ft_get_l_fork(ph);
		if (ft_get_r_fork(ph) == 0)
		{
			ft_get_lunch(ph);
			ft_get_sleep(ph);
			ft_messages(ph, "philosopher is thinking\n", 0);
		}
	}
}*/

/*void	ft_odd_n_philos(t_philo *ph, int must)
{
	if (ph->id == 0 || ph->id == ph->r->n_philos - 1)
		ft_option_b(ph, must);
	else if (ph->id % 2 == 0)
		ft_option_a(ph, must);
	else
		ft_option_b(ph, must);
}
	
void	ft_even_n_philos(t_philo *ph, int must)
{
	if (ph->id == 0 || ph->id == ph->r->n_philos - 1)
		ft_option_b(ph, must);
	else if (ph->id % 2 == 0)
		ft_option_a(ph, must);
	else
		ft_option_b(ph, must);
}*/

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
	ft_option_a(philo, must_continue);
	/*if (philo->r->n_philos % 2)
		ft_odd_n_philos(philo, must_continue);
	else
		ft_even_n_philos(philo, must_continue);*/
}
