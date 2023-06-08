/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:41:47 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 17:00:31 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table, pthread_t supervisor,
	t_philosopher *philosopher)
{
	pthread_join(supervisor, NULL);
	philosopher = table->philosophers;
	while (philosopher)
	{
		pthread_join(philosopher->thread, NULL);
		philosopher = philosopher->next;
	}
}

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philosopher	*philosopher;
	pthread_t		supervisor;

	if (argc < 5)
		return (EXIT_FAILURE);
	table = setup_table((t_table_settings){
			p_atoll(argv[1]), p_atoll(argv[2]),
			p_atoll(argv[3]), p_atoll(argv[4]), 0});
	if (!table)
		return (EXIT_FAILURE);
	if (argc == 6)
		table->settings.must_eat = p_atoll(argv[5]);
	philosopher = table->philosophers;
	while (philosopher)
	{
		pthread_create(&philosopher->thread, NULL, philosopher_routine,
			philosopher);
		philosopher = philosopher->next;
	}
	pthread_create(&supervisor, NULL, supervisor_routine, table);
	join_threads(table, supervisor, philosopher);
	destroy_table(table);
	return (EXIT_SUCCESS);
}
