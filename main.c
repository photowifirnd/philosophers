#include "philo.h"

int	ft_finish(t_rules *r)
{
	size_t i;

	i = 0;
	if (r->philo != NULL)
	{
		while (i < r->n_philos)
		{
			if (r->forks != NULL)
				pthread_mutex_destroy(&r->forks[i]);
			pthread_mutex_destroy(&r->philo[i].mutex);
			pthread_mutex_destroy(&r->philo[i++].eat);
		}
		free(r->philo);
		(r->forks != NULL) ? free(r->forks): NULL;
	}
	pthread_mutex_destroy(&r->philo_dead);
	pthread_mutex_destroy(&r->message);
	//free the rest of malloced objects and init_mutexes;
	return (0);
}

void	ft_messages(t_philo *ph, const char *str, int id_message)
{
	size_t timestamp;

	pthread_mutex_lock(&ph->r->message);
	if (ph->r->is_dead == 0)
	{
		timestamp = ft_time_in_ms();
		ft_putnbr(timestamp);
		write(1, " ", 1);
		ft_putnbr(ph->id + 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		if (id_message == 1)
		{
			ph->r->is_dead = 1;
			write(1, "philosopher's dead at: ", 23);
			ft_putnbr(ph->will_die / 1000);
			ft_putchar('\n');
		}
	}
	pthread_mutex_unlock(&ph->r->message);
}

int	ft_init_threads(t_rules *r)
{
	void		*philo;
	size_t		i;
	pthread_t	thread_id;

	i = 0;
	if (r->n_times_to_eat > 0)
	{
		if (pthread_create(&thread_id, NULL, (void *)ft_count_eaters, (void *)r) != 0)
			return (1);
		pthread_detach(thread_id);
	}
	while (i < r->n_philos)
	{
		philo = (void *)(&r->philo[i]);
		if (pthread_create(&thread_id, NULL, (void *)ft_living, philo) != 0)
			return (1);
		pthread_detach(thread_id);
		i++;
	}
	return (0);
}

int	ft_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_rules	r;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Argument\n"));
	if (ft_init(argc, argv, &r))
		return (1);
	if (ft_init_threads(&r))
		return (1);
	pthread_mutex_lock(&r.philo_dead);
	pthread_mutex_unlock(&r.philo_dead);
	ft_finish(&r);
	return (0);
}
