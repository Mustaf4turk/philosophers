#include "philo.h"

static void	create_philosopher_threads(t_status *status, t_philosopher *philos,
		pthread_t *threads)
{
	int	index;

	index = 0;
	while (index < status->total_philo)
	{
		pthread_create(&threads[index], NULL, start_dinner, &philos[index]);
		index++;
	}
}

static void	wait_for_completion(t_status *status, pthread_t *threads,
		pthread_t monitor)
{
	int	index;

	index = 0;
	while (index < status->total_philo)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
	pthread_join(monitor, NULL);
}

long	print_status(t_philosopher *philo, t_action action)
{
	long	current_time;
	long	time_spent;

	current_time = get_current_time();
	time_spent = current_time - philo->status->start_time;
	pthread_mutex_lock(&philo->status->m_print_status);
	if (action == TAKING_FORK)
		printf(FORK_LOG, time_spent, philo->philo_name);
	else if (action == EATING)
		printf(EAT_LOG, time_spent, philo->philo_name);
	else if (action == SLEEPING)
		printf(SLEEP_LOG, time_spent, philo->philo_name);
	else if (action == DEAD)
		printf(DEATH_LOG, time_spent, philo->philo_name);
	else if (action == THINKING)
		printf(THINK_LOG, time_spent, philo->philo_name);
	pthread_mutex_unlock(&philo->status->m_print_status);
	return (current_time);
}

void	set_dinner(t_status *status, t_philosopher *philos)
{
	pthread_t	*philosopher_threads;
	pthread_t	monitor_thread;

	philosopher_threads = malloc(status->total_philo * sizeof(pthread_t));
	if (!philosopher_threads)
		return ;
	create_philosopher_threads(status, philos, philosopher_threads);
	pthread_create(&monitor_thread, NULL, thread_manager, philos);
	wait_for_completion(status, philosopher_threads, monitor_thread);
	free(philosopher_threads);
}
