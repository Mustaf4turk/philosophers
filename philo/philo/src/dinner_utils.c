/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:57:54 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 09:17:28 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_meal_completion(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->status->m_eaten);
	philo->status->eaten++;
	philo->meal_completed = 1;
	pthread_mutex_unlock(&philo->status->m_eaten);
}

int	should_philosopher_continue(t_philosopher *philo)
{
	int	should_continue;

	pthread_mutex_lock(&philo->status->m_stop);
	should_continue = (philo->status->stop == 0);
	pthread_mutex_unlock(&philo->status->m_stop);
	return (should_continue);
}

void	*handle_single_philosopher(t_philosopher *philo)
{
	print_msg(philo, TAKING_FORK);
	usleep(philo->status->death_time * 1000);
	return (NULL);
}

int	is_stopped(t_status *philo_status)
{
	int	dinner_stopped;

	pthread_mutex_lock(&philo_status->m_stop);
	dinner_stopped = philo_status->stop;
	pthread_mutex_unlock(&philo_status->m_stop);
	return (dinner_stopped);
}

void	*start_dinner(void *philosopher_data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher_data;
	if (philo->status->count == 1)
		return (handle_single_philosopher(philo));
	if (philo->id % 2 == 0)
		usleep(500);
	while (should_philosopher_continue(philo))
	{
		eating(philo);
		if (philo->eat_cnt == philo->status->meal_limit)
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
