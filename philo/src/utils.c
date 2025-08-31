/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muturk <muturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 08:58:17 by muturk            #+#    #+#             */
/*   Updated: 2025/08/31 08:58:18 by muturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mssleep(long ms_time)
{
	long	start;
	long	current;
	long	remaining;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= ms_time)
			break ;
		remaining = ms_time - (current - start);
		if (remaining >= 5)
			usleep(remaining * 500);
		else
			usleep(200);
	}
}
