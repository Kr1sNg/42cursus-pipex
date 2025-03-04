/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multifork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 19:52:17 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
fork() creates a new process (child) by duplicating the calling process (parent)
	pid_t fork(void);
On success, the PID of the child process is returned in the parent,
and 0 is returned in the child. On failure, -1 is returned in the parent,
no child process is created.
*/

/* how to distingue which processes are main (parents) vs children
if we have numerous forks */

/* main ___(1st fork)____ 1a ___(2nd fork)________ 2
		\_______________________(2nd fork)________ 1b
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int ac, char *av[])
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 ==  0)
			printf("we are process child (2) of child (1a)\n");
		else
			printf("we are process child (1a) of main\n");
	}
	else
	{
		if (id2 == 0)
			printf("we are process child (1b) of main\n");
		else
			printf("we are the main\n");
	}

	/* to make sure all children process finish before main process terminates */
	while (wait(NULL) != -1 || errno != ECHILD);
	
	return (0);
}