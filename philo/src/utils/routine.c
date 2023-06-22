/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:05:21 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/22 16:06:24 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_table *table)
{
	bool	stop;

	pthread_mutex_lock(&table->mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->mutex);
	return (stop);
}

void	stop(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	table->stop = true;
	pthread_mutex_unlock(&table->mutex);
}
