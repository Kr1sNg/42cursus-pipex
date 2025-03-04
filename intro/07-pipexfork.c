/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07-pipexfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 21:07:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
we have an array of numbers
- sum all elements up by 2 processes using multi processes
	- [1] sum up a half ahead then sent it to pipe
	- [2] recieve from pipe and sum up with the last half

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int ac, char *av[])
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7, 7};
	int len = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	
	if (pipe(fd) == -1)
	{
		printf("An error occurred with opening pipe\n");
		return (-42);
	}
	int id = fork();
	if (id == -1)
	{
		printf("An error occurred with starting fork\n");
		return (-42);
	}
	if (id == 0)
	{
		start = 0;
		end = len / 2;
	}
	else
	{
		start = len / 2;
		end = len;
	}
	
	int sum = 0;
	int i;
	for (i = start; i < end; i++)
	{
		sum += arr[i];
	}
	printf("Calculated partical sum: %i\n", sum);

	/* if we are in child, we send result back to parent by pipe */
	if (id == 0) // it's child
	{
		close(fd[0]); //we don't read any thing, we send (write) so use only fd[1]
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (-42);
		close(fd[1]);
	}
	else
	{
		int sumofchild;
		close(fd[1]);
		if (read(fd[0], &sumofchild, sizeof(sumofchild)) == -1)
			return (-42);
		close(fd[0]);
		int total = sum + sumofchild;
		printf("Total: %d\n", total);
		wait(NULL);
	}
	return (0);
}
