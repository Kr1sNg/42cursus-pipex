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

/* FIFOs - have to have 2 opens (for reading or for writing) in the same time
if not it will be hanged 
>> Opening the read or write end of a FIFO blocks until the other end is also opened
(by another process or thread)
*/

/* two way communication between processes (using fifo) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int	main(int ac, char *av[])
{
	/* create file with fifo */
	/* we can use directly 'mkfifo' in terminal to create fifo file */
	// if (mkfifo("myfifo1.txt", 0777) == -1) // to give permission chmod execution
	// {
	// 	if (errno != EEXIST)
	// 	{
	// 		printf("Could not create fifo files\n"); // this file will be read from everyone
	// 		return (-42);
	// 	}
	// }

	/* create random arr */
	int arr[5];
	srand(time(NULL));
	int i;
	for (i = 0; i < 5; i++)
	{
		arr[i] = rand() % 100;
		printf("Generated %i\n", arr[i]);
	}

	int fd = open("sum", O_WRONLY);
	if (fd == -1)
		return (-42);
	if (write(fd, arr, sizeof(int) * 5) == -1)
		return (-42);

	int sum;
	close(fd);
	fd = open("sum", O_RDONLY);
	if (fd == -1)
		return (-42);
	if (read(fd, &sum, sizeof(sum)) == -1)
		return (-42);
	printf("received sum: %i\n", sum);
	close(fd);
	
	return (0);
}
/* we have to open write and read in same time */