/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:20:21 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/22 16:44:35 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philosopher *philosopher, char *action)
{
	pthread_mutex_lock(&philosopher->table->mutex);
	if (!philosopher->table->stop)
		printf("%lld %zu %s\n", now() - philosopher->table->t_start,
			philosopher->id, action);
	pthread_mutex_unlock(&philosopher->table->mutex);
}
