#include "philo.h"

int	take_forks_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->m_left_fork);
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_left_fork);
		return (1);
	}
	print_status(philo, TAKING_FORK);
	pthread_mutex_lock(philo->m_right_fork);
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_right_fork);
		pthread_mutex_unlock(philo->m_left_fork);
		return (1);
	}
	print_status(philo, TAKING_FORK);
	return (0);
}

int	take_forks_even(t_philosopher *philo)
{
	pthread_mutex_lock(philo->m_right_fork);
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_right_fork);
		return (1);
	}
	print_status(philo, TAKING_FORK);
	pthread_mutex_lock(philo->m_left_fork);
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_left_fork);
		pthread_mutex_unlock(philo->m_right_fork);
		return (1);
	}
	print_status(philo, TAKING_FORK);
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	if (philo->philo_name % 2 == 1)
		return (take_forks_odd(philo));
	else
		return (take_forks_even(philo));
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->m_right_fork);
	pthread_mutex_unlock(philo->m_left_fork);
}
