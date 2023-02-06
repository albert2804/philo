/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:38:42 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 18:06:35 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	routine(t_philo *philo, t_table *table)
{
	if (table->n_philos == 1)
	{
		print(FORK, philo->n + 1, table);
		wait_func(table->philo_array[0].t2_die + 5);
	}
	else
	{
		eat(philo, table);
		sleeping(philo, table);
		think(philo, table);
	}
}

void	eat(t_philo *philo, t_table *table)
{
	int	rfork;
	int	lfork;

	lfork = 0;
	rfork = 0;
	if (philo->n == table->n_philos - 1)
	{
		lfork = philo->n;
		rfork = 0;
	}
	else
	{
		rfork = philo->n;
		lfork = philo->n + 1;
	}
	pthread_mutex_lock(&table->forks[rfork]);
	print(FORK, philo->n + 1, table);
	pthread_mutex_lock(&table->forks[lfork]);
	print(FORK, philo->n + 1, table);
	pthread_mutex_lock(&table->mutex);
	philo->t_eat = get_current();
	philo->n_eat ++;
	pthread_mutex_unlock(&table->mutex);
	print(EAT, philo->n + 1, table);
	wait_func(philo->t2_eat);
}

void	sleeping(t_philo *philo, t_table *table)
{
	int	rfork;
	int	lfork;

	lfork = 0;
	rfork = 0;
	if (philo->n == table->n_philos - 1)
	{
		lfork = philo->n;
		rfork = 0;
	}
	else
	{
		rfork = philo->n;
		lfork = philo->n + 1;
	}
	print(SLEEP, philo->n + 1, table);
	pthread_mutex_unlock(&table->forks[lfork]);
	pthread_mutex_unlock(&table->forks[rfork]);
	wait_func(philo->t2_sleep);
}

void	think(t_philo *philo, t_table *table)
{
	print(THINK, philo->n + 1, table);
	if (philo->n == table->n_philos - 1)
		wait_func(3);
}

/**
 * this function shall initialize the state at the start of the simulation,
 * where half of the philos will start eating and the other half is thinking,
 * depending if it will be an odd or even numbeer of philos.
 * To accomplish this, the flags have to be set to 
 * o all philos false for sleeping
 * o true for all philos thinking
 * o half of the philos true for eating
*/
void	outset(t_philo *philo, t_table *table)
{	
	print(THINK, philo->n + 1, table);
	if (philo->n % 2 == 0 && philo->n != table->n_philos - 1)
		wait_func(table->philo_array[0].t2_eat + 5);
}
