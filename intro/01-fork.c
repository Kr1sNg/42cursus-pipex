/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 15:52:47 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
fork() creates a new process (child) by duplicating the calling process (parent)
	pid_t fork(void);
On success, the PID of the child process is returned in the parent,
and 0 is returned in the child. On failure, -1 is returned in the parent,
no child process is created.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char *av[])
{
	int id = fork();
	// printf("Hello world from id: %i\n", id);

/*
	id = 0 return in child 
	id != 0 return in the main (parent) process
*/	
	if (id == 0)
		printf("Hello world from child id: %i\n", id);
	else
		printf("Hello world from main id: %i\n", id);
	return (0);
}