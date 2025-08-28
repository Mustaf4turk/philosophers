#include "philo.h"

static void		terminate_simulation(t_status *philo_status);
static int		check_meal_completion(t_status *philo_status);
static int		check_philosopher_death(t_philosopher *philo);
static int		monitor_philosophers(t_philosopher *philos, t_status *status);

void	*thread_manager(void *arg)
{
	t_philosopher	*philosophers;
	t_status		*simulation_status;

	philosophers = (t_philosopher *)arg;
	simulation_status = philosophers[0].status;
	while (!check_meal_completion(simulation_status))
	{
		if (monitor_philosophers(philosophers, simulation_status))
			break ;
		usleep(5000);
	}
	return (NULL);
}

static int	monitor_philosophers(t_philosopher *philos, t_status *status)
{
	int	philosopher_index;

	philosopher_index = 0;
	while (philosopher_index < status->total_philo)
	{
		if (check_philosopher_death(&philos[philosopher_index]))
		{
			terminate_simulation(status);
			print_status(&philos[philosopher_index], DEAD);
			return (1);
		}
		philosopher_index++;
	}
	return (0);
}

static int	is_stuffed(t_status *philo_status)
{
	int	boolean;

	boolean = 0;
	pthread_mutex_lock(&philo_status->m_meals_repeated);
	if (philo_status->meals_repeated == philo_status->total_philo)
		boolean = 1;
	pthread_mutex_unlock(&philo_status->m_meals_repeated);
	return (boolean);
}

static int	died_of_starvation(t_philosopher *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->status->m_last_meal);
	last_meal = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->status->m_last_meal);
	if (last_meal > philo->status->time_of_death)
		return (1);
	return (0);
}

static void	raise_stop_dinner(t_status *philo_status)
{
	pthread_mutex_lock(&philo_status->m_stop_dinner);
	philo_status->stop_dinner = 1;
	pthread_mutex_unlock(&philo_status->m_stop_dinner);
}

static void	terminate_simulation(t_status *philo_status)
{
	raise_stop_dinner(philo_status);
}

static int	check_meal_completion(t_status *philo_status)
{
	if (philo_status->meals_to_eat == -1)
		return (0);
	return (is_stuffed(philo_status));
}

static int	check_philosopher_death(t_philosopher *philo)
{
	return (died_of_starvation(philo));
}
