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
void	eating(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	if (philo->philo_name % 2 == 1)
	{
		if (take_forks_odd(philo))
			return ;
	}
	else
	{
		if (take_forks_even(philo))
			return ;
	}
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_right_fork);
		pthread_mutex_unlock(philo->m_left_fork);
		return ;
	}
	philo->eat_again += 1;
	pthread_mutex_lock(&philo->status->m_last_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->status->m_last_meal);
	print_status(philo, EATING);
	mssleep(philo->status->time_of_eating);
	pthread_mutex_unlock(philo->m_right_fork);
	pthread_mutex_unlock(philo->m_left_fork);
}
void	thinking(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	print_status(philo, THINKING);
}

void	sleeping(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	print_status(philo, SLEEPING);
	mssleep(philo->status->time_of_sleeping);
}
