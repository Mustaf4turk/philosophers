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
	long			time_of_death;
	long			time_of_eating;
	long			time_of_sleeping;
	int				total_philo;
	int				meals_to_eat;
	int				meals_repeated;
	long			start_time;
	int				stop_dinner;
	pthread_mutex_t	m_print_status;
	pthread_mutex_t	m_meals_repeated;
	pthread_mutex_t	m_stop_dinner;
	pthread_mutex_t	m_last_meal;
}	t_status;

typedef struct s_philosopher
{
	int				philo_name;
	int				eat_again;
	int				meal_completed;
	long			last_meal;
	pthread_mutex_t	*m_left_fork;
	pthread_mutex_t	*m_right_fork;
	t_status		*status;
}	t_philosopher;

int				to_natural_nbr(char *arg);
int				is_valid_input(int argc, char **argv);

void			init_status(char **argv, t_status *status);
pthread_mutex_t	*init_forks(t_status *status);
t_philosopher	*init_philosophers(t_status *status, \
						pthread_mutex_t **forks);

void			set_dinner(t_status *status, t_philosopher *philos);
void			*start_dinner(void *philo_sits_down);
int				stop_dinner(t_status *philo_status);
int				should_philosopher_continue(t_philosopher *philo);
long			print_status(t_philosopher *philo, t_action action);
void			*handle_single_philosopher(t_philosopher *philo);

void			eating(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			sleeping(t_philosopher *philo);

void			*thread_manager(void *philosophers);
void			terminate_simulation(t_status *philo_status);
int				monitor_philosophers(t_philosopher *philos, t_status *status);
int				check_meal_completion(t_status *philo_status);
int				check_philosopher_death(t_philosopher *philo);

int				ft_min(int a, int b);
int				ft_max(int a, int b);
long			get_current_time(void);
void			mssleep(long ms_time);

#endif