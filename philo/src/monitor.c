/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:58:14 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 09:17:10 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died_of_starvation(t_philosopher *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->status->m_meal);
	last_meal = get_time() - philo->last;
	pthread_mutex_unlock(&philo->status->m_meal);
	if (last_meal > philo->status->death_time)
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
	while (philosopher_index < status->count)
	{
		pthread_mutex_lock(&status->m_eaten);
		meal_completed = philos[philosopher_index].meal_completed;
		pthread_mutex_unlock(&status->m_eaten);
		if (!meal_completed
			&& check_philosopher_death(&philos[philosopher_index]))
		{
			end_sim(status);
			print_msg(&philos[philosopher_index], DEAD);
			return (1);
		}
		philosopher_index++;
	}
	return (0);
}

static int	is_full(t_status *philo_status)
{
	int	boolean;

	boolean = 0;
	pthread_mutex_lock(&philo_status->m_eaten);
	if (philo_status->eaten == philo_status->count)
		boolean = 1;
	pthread_mutex_unlock(&philo_status->m_eaten);
	return (boolean);
}

int	check_all_ate(t_status *philo_status)
{
	if (philo_status->meal_limit == -1)
		return (0);
	return (is_full(philo_status));
}
