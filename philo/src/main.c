/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:41:47 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:53:29 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philosopher	*philosopher;
	pthread_t		supervisor;

	table = NULL;
	if (argc == 5)
		table = setup_table(p_atoll(argv[1]), p_atoll(argv[2]),
				p_atoll(argv[3]), p_atoll(argv[4]), 0);
	else if (argc == 6)
		table = setup_table(p_atoll(argv[1]), p_atoll(argv[2]),
				p_atoll(argv[3]), p_atoll(argv[4]), p_atoll(argv[5]));
	if (!table)
		return (EXIT_FAILURE);
	philosopher = table->philosophers;
	while (philosopher)
	{
		pthread_create(&philosopher->thread, NULL, philosopher_routine,
			philosopher);
		philosopher = philosopher->next;
	}
	pthread_create(&supervisor, NULL, supervisor_routine, table);
	pthread_join(supervisor, NULL);
	destroy_table(table);
	return (EXIT_SUCCESS);
}
