/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:58:24 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:46:57 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Get the current time in milliseconds
/// @return The current time in milliseconds
long long	now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/// @brief Wait for a certain amount of time
/// using small usleep to avoid busy waiting
/// @param ms The amount of time to wait in milliseconds
void	p_usleep(long long ms)
{
	long long	delay;
	long long	start;

	delay = ms / 10;
	if (ms < 10)
		delay = 1;
	start = now();
	while (now() - start < ms)
		usleep(delay);
}
