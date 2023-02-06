/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:25:56 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:10:46 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_philo(int argc, char **argv, t_table *table)
{
	(void)argc;
	init_allocs(argv, table);
	init_table(argv, table);
}

/**
 * cleanup function frees all allocations which are connecetd to mallocstruct
*/
void	ft_cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
		pthread_mutex_destroy(&table->forks[i ++]);
	pthread_mutex_destroy(&table->mutex_spawn);
	pthread_mutex_destroy(&table->mutex_print);
	if (table->allocations.forks)
		free(table->allocations.forks);
	if (table->allocations.philo_array)
		free(table->allocations.philo_array);
	if (table->allocations.thread_array)
		free(table->allocations.thread_array);
	if (table)
		free(table);
}

/**
 * takes a variable size and times (like in calloc),
 * and sets the alloced array to the pointer of the malloc_struct.
*/
void	*advanced_calloc(size_t size, size_t times, void **malloc_struct)
{
	void	*array;

	array = calloc(size, times);
	if (!array)
		return (NULL);
	(void) malloc_struct;
	*malloc_struct = array;
	return (array);
}

void	init_allocs(char **argv, t_table *table)
{
	table->thread_array = advanced_calloc (sizeof(pthread_t), ft_atoi(argv[1]) \
	+ 1, (void *) &table->allocations.thread_array);
	if (!table->thread_array)
		ft_cleanup(table);
	table->philo_array = advanced_calloc (sizeof(t_philo), ft_atoi(argv[1]), \
	(void *) &table->allocations.philo_array);
	if (!table->philo_array)
		ft_cleanup(table);
	table->forks = advanced_calloc (sizeof(pthread_mutex_t), ft_atoi(argv[1]), \
	(void *) &table->allocations.forks);
	if (!table->forks)
		ft_cleanup(table);
}

void	init_table(char **argv, t_table *table)
{
	int	i;

	i = 0;
	table->starttime = get_current();
	table->i = 0;
	table->delta = 0;
	table->n_eat = 0;
	table->n_philos = ft_atoi(argv[1]);
	pthread_mutex_init(&table->mutex_spawn, NULL);
	pthread_mutex_init(&table->mutex_print, NULL);
	pthread_mutex_init(&table->mutex_timestamp, NULL);
	while (i < ft_atoi(argv[1]))
	{
		table->philo_array[i].n = i;
		table->philo_array[i].eat = false;
		table->philo_array[i].t2_die = ft_atoi(argv[2]);
		table->philo_array[i].t2_eat = ft_atoi(argv[3]);
		table->philo_array[i].t2_sleep = ft_atoi(argv[4]);
		if (argv[5])
			table->philo_array[i].eat_total = ft_atoi(argv[5]) + 1;
		else
			table->philo_array[i].eat_total = 1000000;
		table->philo_array[i].table = table;
		pthread_mutex_init(&table->forks[i ++], NULL);
	}
}
