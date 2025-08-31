/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:00:53 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 17:11:26 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK_LOG	"%-5ld %2d has taken a fork\n"
# define EAT_LOG	"%-5ld %2d is eating\n"
# define SLEEP_LOG	"%-5ld %2d is sleeping\n"
# define THINK_LOG	"%-5ld %2d is thinking\n"
# define DEATH_LOG	"%-5ld %2d died\n"

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_action;

typedef struct s_status
{
	long			death_time;
	long			eat_time;
	long			sleep_time;
	int				count;
	int				meal_limit;
	int				eaten;
	long			start_time;
	int				stop;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_eaten;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_meal;
}	t_status;

typedef struct s_philosopher
{
	int				id;
	int				eat_cnt;
	int				meal_completed;
	long			last;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_status		*status;
}	t_philosopher;

int				to_nbr(char *str);
int				is_valid(int argc, char **argv);

void			init_status(char **argv, t_status *status);
pthread_mutex_t	*init_forks(t_status *status);
t_philosopher	*init_philosophers(t_status *status, \
						pthread_mutex_t **forks);

void			end_sim(t_status *data);
void			set_dinner(t_status *status, t_philosopher *philos);
void			*start_dinner(void *philo_sits_down);
int				is_stopped(t_status *data);
int				should_philosopher_continue(t_philosopher *philo);
long			print_msg(t_philosopher *philo, t_action action);
void			*handle_single_philosopher(t_philosopher *philo);

void			eating(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			sleeping(t_philosopher *philo);

int				take_odd(t_philosopher *philo);
int				take_even(t_philosopher *philo);
int				take_forks(t_philosopher *philo);
void			drop_forks(t_philosopher *philo);

void			*thread_manager(void *philosophers);
void			set_stop(t_status *data);
int				monitor_philosophers(t_philosopher *philos, t_status *status);
int				check_all_ate(t_status *data);
int				check_philosopher_death(t_philosopher *philo);

int				min(int a, int b);
int				max(int a, int b);
long			get_time(void);
void			mssleep(long ms_time);

#endif