/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:58:06 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 09:12:32 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_philosopher *philos, pthread_mutex_t *m_forks)
{
	int	i;

	i = -1;
	while (++i < philos->status->count)
		pthread_mutex_destroy(&m_forks[i]);
	pthread_mutex_destroy(&philos->status->m_print);
	pthread_mutex_destroy(&philos->status->m_eaten);
	pthread_mutex_destroy(&philos->status->m_stop);
	pthread_mutex_destroy(&philos->status->m_meal);
	free(m_forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*m_forks;
	t_philosopher	*philos;
	t_status		status;

	if (!is_valid(argc, argv))
	{
		printf("Invalid args: usage is <nbr_of_philo>(>= 1) "\
				"<time_to_die>(>= 1) <time_to_eat>(>= 1) "\
				"<time_to_sleep>(>= 1) <must_eat>(optional).\n");
		return (1);
	}
	init_status(argv, &status);
	m_forks = init_forks(&status);
	if (!m_forks)
		return (1);
	philos = init_philosophers(&status, &m_forks);
	if (!philos)
	{
		free(m_forks);
		return (1);
	}
	set_dinner(&status, philos);
	free_data(philos, m_forks);
	return (0);
}
