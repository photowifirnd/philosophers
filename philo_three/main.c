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
	ft_finish(&r);
	return (0);
}
