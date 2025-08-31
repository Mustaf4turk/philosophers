/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:59:04 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 08:59:05 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (is_stopped(philo->status))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	print_msg(philo, TAKING_FORK);
	pthread_mutex_lock(philo->r_fork);
	if (is_stopped(philo->status))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	print_msg(philo, TAKING_FORK);
	return (0);
}

int	take_even(t_philosopher *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (is_stopped(philo->status))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	print_msg(philo, TAKING_FORK);
	pthread_mutex_lock(philo->l_fork);
	if (is_stopped(philo->status))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	print_msg(philo, TAKING_FORK);
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	if (philo->status->count == 2)
	{
		if (philo->id == 1)
			return (take_odd(philo));
		else
			return (take_odd(philo));
	}
	if (philo->id % 2 == 1)
		return (take_odd(philo));
	else
		return (take_even(philo));
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
