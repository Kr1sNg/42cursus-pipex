/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 17:36:46 by tat-nguy         ###   ########.fr       */
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
	int id = fork();
	if (id == 0)
		sleep(1);
	
	printf("Current's ID	: %i\n", getpid());
	printf("Parent's ID	: %i\n", getppid());
	
	int res = wait(NULL);
	if (res == -1)
		printf("No child to wait for\n");
	else
		printf("%d finished execution\n", res);
	return (0);
}
