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
	t_philo		*philo;
	size_t		i;

	ft_start_counting(r);
	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 0)
		{
			philo = (&r->philo[i]);
			if ((philo->pid = fork()) < 0)
				return (1);
			else if (philo->pid == 0)
			{
				ft_living(philo);
				exit(0);
			}
		}
		i++;
	}
	usleep(200);
	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 1)
		{
			philo = (&r->philo[i]);
			if ((philo->pid = fork()) < 0)
				return (1);
			else if (philo->pid == 0)
			{
				ft_living(philo);
				exit(0);
			}
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
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Argument\n"));
	if (ft_init(argc, argv, &r))
		return (1);
	if (ft_init_threads(&r))
		return (1);
	sem_wait(r.philo_dead);
	i = 0;
	while (i < (int)r.n_philos)
		kill(r.philo[i++].pid, SIGKILL);
//	ft_finish(&r); Falta implementar el limpiado y liberado de los semaforos
	return (0);
}
