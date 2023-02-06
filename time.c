/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:07:58 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 18:13:42 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
/**
 * returns the time-difference [ms]between the current time and a startingtime
*/
long long	get_delta(long long starttime)
{
	struct timeval	time;
	long long		delta;

	gettimeofday(&time, NULL);
	delta = get_current() - starttime;
	return (delta);
}

/**
 * returns the current time[ms]
*/
long long	get_current(void)
{
	long long		current_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

/**
 * wait fnction which calls usleep and is more precise than only using usleep
*/
void	wait_func(long long time_in_ms)
{
	long long	starttime;

	starttime = get_current();
	while (get_delta(starttime) <= time_in_ms)
		usleep(1000);
}
