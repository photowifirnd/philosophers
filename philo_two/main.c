#include "philo.h"

/*int	ft_finish(t_rules *r)
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
}*/

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
	return (ft_set_general(argc, argv, r) || ft_set_philos(r) || ft_set_forks(r));
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
	sem_wait(r.philo_dead);
//	ft_finish(&r); Falta implementar el limpiado y liberado de los semaforos
	return (0);
}
