/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:19:35 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/22 16:47:10 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_meals(t_philosopher *philosopher)
{
	long long	meals;

	pthread_mutex_lock(&philosopher->mutex);
	meals = philosopher->meals;
	pthread_mutex_unlock(&philosopher->mutex);
	return (meals);
}

static long long	get_t_meal(t_philosopher *philosopher)
{
	long long	t_meal;

	pthread_mutex_lock(&philosopher->mutex);
	t_meal = philosopher->t_meal;
	pthread_mutex_unlock(&philosopher->mutex);
	return (t_meal);
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
	while (!should_stop(table))
	{
		finished = 0;
		philosopher = table->philosophers;
		while (philosopher)
		{
			if (table->settings.tt_die < now() - get_t_meal(philosopher))
			{
				log_action(philosopher, "died", RED);
				return (stop(table), NULL);
			}
			if (table->settings.must_eat > 0 && get_meals(philosopher) >= table->settings.must_eat)
				finished++;
			philosopher = philosopher->next;
		}
		if (finished == table->settings.n_philosophers)
			return (stop(table), NULL);
	}
	return (NULL);
}
