/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:58:10 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 09:16:51 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_manager(void *arg)
{
	t_philosopher	*philosophers;
	t_status		*simulation_status;

	philosophers = (t_philosopher *)arg;
	simulation_status = philosophers[0].status;
	while (!check_all_ate(simulation_status))
	{
		if (monitor_philosophers(philosophers, simulation_status))
			break ;
		usleep(1000);
	}
	if (check_all_ate(simulation_status))
		end_sim(simulation_status);
	return (NULL);
}

void	set_stop(t_status *philo_status)
{
	pthread_mutex_lock(&philo_status->m_stop);
	philo_status->stop = 1;
	pthread_mutex_unlock(&philo_status->m_stop);
}

void	end_sim(t_status *philo_status)
{
	set_stop(philo_status);
}

int	get_sim(t_status *philo_status)
{
	int	simulation;

	pthread_mutex_lock(&philo_status->m_stop);
	simulation = philo_status->stop;
	pthread_mutex_unlock(&philo_status->m_stop);
	return (simulation);
}
