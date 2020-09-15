#include "philo.h"

int	ft_finish(t_rules *r)
{
	size_t i;
	char	str[250];

	sem_unlink("SemForks");
	sem_unlink("WriteMessage");
	sem_unlink("PhiloDead");
	i = 0;
	if (r->philo != NULL)
	{
		while (i < r->n_philos)
		{
			ft_sem_name("SemMutex", (char *)str, i);
			sem_unlink(str);
			ft_sem_name("SemEat", (char *)str, i++);
			sem_unlink(str);
		}
	}
	return (0);
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
	ft_finish(&r);
	return (0);
}
