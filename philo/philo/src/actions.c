#include "philo.h"

static void	perform_eating(t_philosopher *philo)
{
	philo->eat_again += 1;
	pthread_mutex_lock(&philo->status->m_last_meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->status->m_last_meal);
	print_status(philo, EATING);
	mssleep(philo->status->time_of_eating);
}

void	eating(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	if (take_forks(philo))
		return ;
	if (stop_dinner(philo->status))
	{
		release_forks(philo);
		return ;
	}
	perform_eating(philo);
	release_forks(philo);
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
