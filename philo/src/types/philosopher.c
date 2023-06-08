/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:15:16 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/05 20:32:59 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Create a new philosopher
/// @param id The philosopher's id
/// @return The philosopher created, or NULL if an error occured
t_philosopher	*new_philosopher(size_t id, t_table *table)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	philosopher->table = table;
	if (id % 2)
		philosopher->state = SLEEPING;
	else
		philosopher->state = THINKING;
	philosopher->t_meal = table->t_start;
	philosopher->meals = 0;
	pthread_mutex_init(&philosopher->fork, NULL);
	philosopher->neighbour_fork = NULL;
	philosopher->next = NULL;
	return (philosopher);
}

/// @brief Destroy a philosopher
/// @param philosopher The philosopher to destroy
/// @return void
void	destroy_philosopher(t_philosopher *philosopher)
{
	pthread_mutex_destroy(&philosopher->fork);
	pthread_detach(philosopher->thread);
	free(philosopher);
}
