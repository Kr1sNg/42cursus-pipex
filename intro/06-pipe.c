/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06-pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 20:30:26 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int	pipe(int pipefd[2]);
The pipe() creates a pipe, a unidirectional data channel
that can be used for interprocess communication. 
The array pipefd[2] is used to return two file descriptors 
referring to the ends of the pipe:

pipefd[0]: refers to the read end of the pipe (data comes out here).
pipefd[1]: refers to the write end of the pipe (data goes in here).

	pipefd[0] - read - stdin
	pipefd[1] - write - stdout

*/
/* communicate between processes parent and chid using pipes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char *av[])
{
	int fd[2];
	/* fd[0] stdin - fd[1] stdout */
	/* create pipe (file) before fork() */
	if (pipe(fd) == -1)
	{
		printf("An error occurred with opening pipe\n");
		return (-42);
	}
	int id = fork();
	if (id == -1)
	{
		printf("An error occurred with opening pipe\n");
		return (-42);
	}
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number to send back to parent process: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			return (-42);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (-42);
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	
	return (0);
}