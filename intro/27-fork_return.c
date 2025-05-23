/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27-fork_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 20:57:34 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
getpid() returns the process ID (PID) of the calling process.
getppid() returns the process ID of the parent of the calling process.
		pid_t getpid(void);
       	pid_t getppid(void);

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int ac, char *av[])
{
	int id = fork(); //fork return ?
	// inside parent process - fork return "child process id" - it's going different than getpid()
	// inside child process - fork return "0" - it's going to different than getpid() too

	if (id == 0)
		sleep(1);
	
	printf("return by fork: %i, Current's ID: %i, Parent's ID: %i\n", id, getpid(), getppid());
	
	int res = wait(NULL);
	if (res == -1)
		printf("No child to wait for\n");
	else
		printf("%d finished execution\n", res);
	return (0);
}
