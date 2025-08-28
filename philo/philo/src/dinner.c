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

static int	should_philosopher_continue(t_philosopher *philo)
{
	int	should_continue;

	pthread_mutex_lock(&philo->status->m_stop_dinner);
	should_continue = (philo->status->stop_dinner == 0);
	pthread_mutex_unlock(&philo->status->m_stop_dinner);
	return (should_continue);
}

static void	handle_meal_completion(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->status->m_meals_repeated);
	philo->status->meals_repeated++;
	pthread_mutex_unlock(&philo->status->m_meals_repeated);
}

void	*start_dinner(void *philosopher_data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher_data;
	if (philo->status->total_philo == 1)
		return (handle_single_philosopher(philo));
	if (philo->philo_name % 2 == 0)
		usleep(philo->status->time_of_eating * 500);
	while (should_philosopher_continue(philo))
	{
		eating(philo);
		if (philo->eat_again == philo->status->meals_to_eat)
		{
			handle_meal_completion(philo);
			return (NULL);
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
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
		printf(FORK_LOG FORK_LOG EAT_LOG, time_spent, \
					philo->philo_name, time_spent, philo->philo_name, \
					time_spent, philo->philo_name);
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
