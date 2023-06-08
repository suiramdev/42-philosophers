/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:19:35 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 16:57:49 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	table->stop = true;
	pthread_mutex_unlock(&table->mutex);
}

/// @brief The supervisor's routine
/// @param arg The routine's parameters (t_table) @return void
void	*supervisor_routine(void *arg)
{
	t_table			*table;
	t_philosopher	*philosopher;
	size_t			finished;

	table = (t_table *)arg;
	p_usleep(table->t_start - now());
	while (1)
	{
		finished = 0;
		philosopher = table->philosophers;
		while (philosopher)
		{
			if (table->settings.tt_die <= now() - philosopher->t_meal)
				return (stop(table), log_action(philosopher, "died"), NULL);
			if (table->settings.must_eat > 0
				&& philosopher->meals >= table->settings.must_eat)
				finished++;
			philosopher = philosopher->next;
		}
		if (finished == table->settings.n_philosophers)
			return (stop(table), NULL);
	}
	return (NULL);
}
