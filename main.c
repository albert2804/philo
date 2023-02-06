/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:36:03 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:10:04 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	table = calloc(sizeof(t_table), 1);
	if (!table)
		return (0);
	if (argc < 5 || argc > 6)
		return (printf("Wrong Input"), 0);
	if ((ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || \
	ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0) && !argv[5])
		return (ft_cleanup(table), printf("Wrong Input"), 0);
	else if (argv[5] && ft_atoi(argv[5]) < 0)
		return (ft_cleanup(table), printf("Wrong Input"), 0);
	init_philo(argc, argv, table);
	create_philosophers(table->n_philos, table);
	ft_cleanup(table);
}
