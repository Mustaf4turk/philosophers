#include "philo.h"

static void	handle_meal_completion(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->status->m_meals_repeated);
	philo->status->meals_repeated++;
	philo->meal_completed = 1;
	pthread_mutex_unlock(&philo->status->m_meals_repeated);
}

int	should_philosopher_continue(t_philosopher *philo)
{
	int	should_continue;

	pthread_mutex_lock(&philo->status->m_stop_dinner);
	should_continue = (philo->status->stop_dinner == 0);
	pthread_mutex_unlock(&philo->status->m_stop_dinner);
	return (should_continue);
}

void	*handle_single_philosopher(t_philosopher *philo)
{
	print_status(philo, TAKING_FORK);
	usleep(philo->status->time_of_death * 1000);
	return (NULL);
}

int	stop_dinner(t_status *philo_status)
{
	int	dinner_stopped;

	pthread_mutex_lock(&philo_status->m_stop_dinner);
	dinner_stopped = philo_status->stop_dinner;
	pthread_mutex_unlock(&philo_status->m_stop_dinner);
	return (dinner_stopped);
}

void	*start_dinner(void *philosopher_data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher_data;
	if (philo->status->total_philo == 1)
		return (handle_single_philosopher(philo));
	if (philo->philo_name % 2 == 0)
		usleep(500);
	while (should_philosopher_continue(philo))
	{
		eating(philo);
		if (philo->eat_again == philo->status->meals_to_eat)
		{
			handle_meal_completion(philo);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	while (should_philosopher_continue(philo))
		usleep(1000);
	return (NULL);
}
