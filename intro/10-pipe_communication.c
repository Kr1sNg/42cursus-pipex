/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-pipe_communication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 15:14:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* programe generate a number in process [1] then send it to process [2]
to multiply it 4 times then send back to process [1] */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int	main(int ac, char *av[])
{
	/* each process have 2 pipes after fork */
	int p1[2]; // child to parent
	int p2[2]; // parent to child
	if (pipe(p1) == -1)
		return -42;
	if (pipe(p2) == -1)
		return -42;
	
	int pid = fork();
	if (pid == -1)
		return -42;
	if (pid == 0) //child process
	{
		close(p1[0]);
		close(p2[1]);
		int x;
		if (read(p2[0], &x, sizeof(x)) == -1)
			return (-42);
		printf("2received %i in pid %i\n", x, getpid());
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return (-42);
		printf("3wrote %d in pid %i\n", x, getpid());
		close(p1[1]);
		close(p2[0]); // always close before read and write
	}
	else // parent process
	{
		close(p1[1]);
		close(p2[0]);
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return (-42);
		/* if we use only 1 pipe, program will stuck if we don't printf below */
		// printf("1wrote %i in pid %i\n", y, getpid());
		if (read(p1[0], &y, sizeof(y)) == -1)
			return (-42);
		printf("4result is %i in pid %i\n", y, getpid());
		close(p1[0]);
		close(p2[1]); // always close before read and write
		wait(NULL);
	}
	
	
	return (0);
}

