#include "philo.h"

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
	if (check_meal_completion(simulation_status))
		terminate_simulation(simulation_status);
	return (NULL);
}

static void	raise_stop_dinner(t_status *philo_status)
{
	pthread_mutex_lock(&philo_status->m_stop_dinner);
	philo_status->stop_dinner = 1;
	pthread_mutex_unlock(&philo_status->m_stop_dinner);
}

void	terminate_simulation(t_status *philo_status)
{
	raise_stop_dinner(philo_status);
}
