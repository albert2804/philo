/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:27:23 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:08:27 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print(int action, int philo, t_table *table)
{
	long long	delta;

	pthread_mutex_lock(&table->mutex_print);
	pthread_mutex_lock(&table->mutex_timestamp);
	delta = get_delta(table->starttime);
	pthread_mutex_unlock(&table->mutex_timestamp);
	pthread_mutex_lock(&table->mutex);
	if (table->die == false)
	{
		pthread_mutex_unlock(&table->mutex);
		if (action == 0)
			printf("%lld %d has taken a fork\n", delta, philo);
		else if (action == 1)
			printf("%lld %d is eating\n", delta, philo);
		else if (action == 2)
			printf("%lld %d is sleeping\n", delta, philo);
		else if (action == 3)
			printf("%lld %d is thinking\n", delta, philo);
	}
	else if (action == 4)
		print_die(delta, philo, table);
	else
		pthread_mutex_unlock(&table->mutex);
	pthread_mutex_unlock(&table->mutex_print);
}

void	print_die(long long delta, int philo, t_table *table)
{
	pthread_mutex_unlock(&table->mutex);
	printf("%lld %d died\n", delta, philo);
}

void	nos1(t_table *table)
{
	pthread_mutex_unlock(&table->mutex);
	pthread_mutex_lock(&table->mutex);
}

void	nos2(t_table *table)
{
	table->j ++;
	pthread_mutex_unlock(&table->mutex);
	usleep(150);
}
