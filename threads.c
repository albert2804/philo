/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:40:51 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:37:59 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*thread_obsrv(void *arg)
{
	t_table		*t;
	t_philo		*philo;

	t = arg;
	philo = t->philo_array;
	set_eatingtime(t, philo);
	while (1)
	{
		while (t->j < t->n_philos)
		{
			pthread_mutex_lock(&t->mutex);
			if (get_current() - philo[t->j].t_eat > philo[t->j].t2_die)
				return (death_checker(t), NULL);
			nos1(t);
			if (philo[t->j].n_eat >= philo[t->j].eat_total + 1)
			{
				philo[t->j].eat = true;
				t->k ++;
				if (t->k == t->n_philos + 1)
					return (t->die = 1, pthread_mutex_unlock(&t->mutex), NULL);
			}
			nos2(t);
		}
		t->j = 0;
	}
}

// This function will be executed by the new thread
void	*thread_function(void *arg)
{
	t_table	*table;
	t_philo	*philo;

	philo = arg;
	table = philo->table;
	outset(philo, table);
	pthread_mutex_lock(&table->mutex);
	while (table->die == false)
	{
		pthread_mutex_unlock(&table->mutex);
		routine(philo, table);
		pthread_mutex_lock(&table->mutex);
	}
	pthread_mutex_unlock(&table->mutex);
	return (NULL);
}

int	create_philosophers(int nbr, t_table *table)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&table->mutex_spawn);
	while (i < nbr + 1)
	{
		if (pthread_create(&table->thread_array[i], NULL, thread_function, \
		&table->philo_array[i - 1]) != 0)
			return (printf("Error creating philo thread\n"), 0);
		i ++;
	}
	pthread_mutex_lock(&table->mutex_timestamp);
	table->starttime = get_current();
	pthread_mutex_unlock(&table->mutex_timestamp);
	pthread_mutex_unlock(&table->mutex_spawn);
	if (pthread_create(&table->thread_array[0], NULL, thread_obsrv, table) != 0)
		return (printf("Error creating obsverver thread\n"), 0);
	i = 0;
	while (i < nbr + 1)
		pthread_join(table->thread_array[i ++], NULL);
	return (1);
}

void	set_eatingtime(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->mutex);
	while (table->j < table->n_philos)
	{
		philo[table->j].t_eat = table->starttime;
		table->j ++;
	}
	table->j = 0;
	pthread_mutex_unlock(&table->mutex);
}

void	death_checker(t_table *table)
{
	table->die = true;
	table->die_philo = table->j;
	pthread_mutex_unlock(&table->mutex);
	print(DEATH, table->die_philo + 1, table);
}
