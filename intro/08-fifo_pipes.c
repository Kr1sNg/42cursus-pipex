/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08-fifo_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 22:10:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FIFO - pipe: first in first out */

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

/* FIFOs - have to have 2 opens (for reading or for writing) in the same time
if not it will be hanged 
>> Opening the read or write end of a FIFO blocks until the other end is also opened
(by another process or thread)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int	main(int ac, char *av[])
{
	if (mkfifo("myfifo1.txt", 0777) == -1) // to give permission chmod execution
	{
		if (errno != EEXIST)
		{
			printf("Could not create fifo files\n"); // this file will be read from everyone
			return (-42);
		}
	}
	printf("Openning...\n");
	int fd = open("myfifo1.txt", O_WRONLY);
	// int fd = open("myfifo1.txt", O_RDWR);
	if (fd == -1)
		return (-42);
	printf("Opened\n");
	int x = 'Z';
	if (write(fd, &x, sizeof(x)) == -1)
		return (-42);
	printf("Written\n");
	close(fd);
	printf("Closed\n");
	
	return (0);
}
/*
=>> so after compiler this code, we need to open other terminal to open myfifo1 file (can simply use 'cat') 

=>> same when we 'cat' myfifo1, we need to open other terminal to read / write into myfifo1 in same time
*/
