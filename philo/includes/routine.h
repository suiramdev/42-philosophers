/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:49:24 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:52:31 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "types.h"

typedef struct s_routine_params
{
	t_table			*table;
	t_philosopher	*philosopher;
}	t_routine_params;

void	*philosopher_routine(void *args);
void	*supervisor_routine(void *args);

#endif
