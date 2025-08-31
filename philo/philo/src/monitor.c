#include "philo.h"

void	terminate_simulation(t_status *philo_status);

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

int	check_philosopher_death(t_philosopher *philo)
{
	return (died_of_starvation(philo));
}

int	monitor_philosophers(t_philosopher *philos, t_status *status)
{
	int	philosopher_index;
	int	meal_completed;

	philosopher_index = 0;
	while (philosopher_index < status->total_philo)
	{
		pthread_mutex_lock(&status->m_meals_repeated);
		meal_completed = philos[philosopher_index].meal_completed;
		pthread_mutex_unlock(&status->m_meals_repeated);
		if (!meal_completed && 
			check_philosopher_death(&philos[philosopher_index]))
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

int	check_meal_completion(t_status *philo_status)
{
	if (philo_status->meals_to_eat == -1)
		return (0);
	return (is_stuffed(philo_status));
}
