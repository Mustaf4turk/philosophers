/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:58:03 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 08:58:04 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_status(char **argv, t_status *status)
{
	status->count = to_nbr(argv[1]);
	status->death_time = to_nbr(argv[2]);
	status->eat_time = to_nbr(argv[3]);
	status->sleep_time = to_nbr(argv[4]);
	status->meal_limit = -1;
	if (argv[5])
		status->meal_limit = to_nbr(argv[5]);
	status->eaten = 0;
	status->start_time = get_time();
	status->stop = 0;
	pthread_mutex_init(&status->m_print, NULL);
	pthread_mutex_init(&status->m_eaten, NULL);
	pthread_mutex_init(&status->m_stop, NULL);
	pthread_mutex_init(&status->m_meal, NULL);
}

pthread_mutex_t	*init_forks(t_status *status)
{
	pthread_mutex_t	*m_forks;
	int				i;

	m_forks = malloc(status->count * sizeof(pthread_mutex_t));
	if (!m_forks)
		return (NULL);
	i = -1;
	while (++i < status->count)
		pthread_mutex_init(&m_forks[i], NULL);
	return (m_forks);
}

t_philosopher	*init_philosophers(t_status *status, pthread_mutex_t **m_forks)
{
	t_philosopher	*philos;
	int				i;

	philos = malloc(status->count * sizeof(t_philosopher));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < status->count)
	{
		philos[i].id = i + 1;
		philos[i].l_fork = \
			&(*m_forks)[min(i, ((i + 1) % status->count))];
		philos[i].r_fork = \
			&(*m_forks)[max(i, ((i + 1) % status->count))];
		philos[i].status = status;
		philos[i].eat_cnt = 0;
		philos[i].meal_completed = 0;
		philos[i].last = status->start_time;
		i++;
	}
	return (philos);
}
