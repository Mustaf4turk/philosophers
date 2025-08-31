/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:57:58 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 15:33:44 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	perform_eating(t_philosopher *philo)
{
	philo->eat_cnt += 1;
	pthread_mutex_lock(&philo->status->m_meal);
	philo->last = get_time();
	pthread_mutex_unlock(&philo->status->m_meal);
	print_msg(philo, EATING);
	mssleep(philo->status->eat_time);
}

void	eating(t_philosopher *philo)
{
	if (is_stopped(philo->status))
		return ;
	if (take_forks(philo))
		return ;
	if (is_stopped(philo->status))
	{
		drop_forks(philo);
		return ;
	}
	perform_eating(philo);
	drop_forks(philo);
}

void	thinking(t_philosopher *philo)
{
	if (is_stopped(philo->status))
		return ;
	print_msg(philo, THINKING);
}

void	sleeping(t_philosopher *philo)
{
	if (is_stopped(philo->status))
		return ;
	print_msg(philo, SLEEPING);
	mssleep(philo->status->sleep_time);
}
