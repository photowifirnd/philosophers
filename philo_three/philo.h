/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:45:08 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 09:47:37 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

struct s_rules;

typedef struct		s_philo
{
	unsigned int	id;
	pid_t			pid;
	int				r_hand;
	int				l_hand;
	int				eat_flag;
	uint64_t		will_die;
	uint64_t		last_eat;
	int				cnt;
	sem_t			*mutex;
	sem_t			*eat;
	struct s_rules	*r;
}					t_philo;

typedef struct		s_rules
{
	unsigned int	n_philos;
	int				*n_forks;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	int				is_dead;
	size_t			n_times_to_eat;
	t_philo			philo[200];
	sem_t			*forks;
	sem_t			*philo_dead;
	sem_t			*message;
	sem_t			*fork_state;
}					t_rules;

int					ft_set_philos(t_rules *r);
int					ft_set_forks(t_rules *r);
int					ft_set_general(int argc, char *argv[], t_rules *r);
int					ft_init(int argc, char *argv[], t_rules *r);
int					ft_init_even(t_rules *r);
int					ft_init_counters(t_rules *r);
void				ft_living(void *ph);
void				ft_eat_or_die(void *ph);
void				ft_count_eaters(void *rules);
int					ft_get_r_fork(t_philo *ph);
void				ft_get_l_fork(t_philo *ph);
void				ft_get_lunch(t_philo *ph);
void				ft_leave_forks(t_philo *ph);
int					ft_error(const char *str);
void				ft_messages(t_philo *ph, const char *str, int id_message);
void				ft_end_message(t_philo *ph, int id_message);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
int					ft_strcpy(char *dst, const char *src);
int					ft_write_message(const char *str);
uint64_t			ft_time_in_ms(void);
uint64_t			ft_time_in_micro_s(void);
void				ft_putchar(char c);
void				ft_putnbr(long long int num);
sem_t				*ft_sem_open(const char *str, int val);
char				*ft_sem_name(const char *str, char *buff, int pos);
int					ft_start_counting(t_rules *r);
#endif
