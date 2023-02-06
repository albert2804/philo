/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:03:41 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:04:38 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *nptr)
{
	int	r;
	int	vz;
	int	i;

	i = 0;
	r = 0;
	vz = 1;
	while (nptr [i] == '\t' || nptr[i] == ' ' || nptr[i] == '\n'\
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
	{
		vz = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && ft_isdigit((int)nptr[i]) == 1)
	{
		r = (r * 10 + nptr[i]) - '0';
		i++;
	}
	return (r * vz);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}
