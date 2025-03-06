/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/06 17:36:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* send signal to the terminal, ctr-Z can't stop the program */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// generate 2 processes
// 1) child process generate random numbers and send them to the parent
// 2) parent is going to sum all the numbers and print the result

int main(int ac, char **av)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (-42);
	
	int pid = fork();
	if (pid == -1)
		return (-42);
	
	if (pid == 0)
	{
		close(fd[0]);
		int n, i;
		int arr[10];
		srand(time(NULL));
		n = rand() % 10 + 1;
		for (i = 0; i < n; i++)
		{
			arr[i] = rand() % 11;
			printf("Number %i: %i\n", i + 1, arr[i]);
		}
		if (write(fd[1], &n, sizeof(int)) < 0) // send at first the number of number in arr
			return (-42);
		if (write(fd[1], arr, sizeof(int) * n) < 0) // then send arr
			return (-42);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int arr[10];
		int n, i , sum = 0;
		if (read(fd[0], &n, sizeof(int)) < 0)
			return (-42);
		if (read(fd[0], arr, sizeof(int) * n) < 10)
			return (-42);
		for (i = 0; i < n; i++)
			sum += arr[i];
		printf("Result is: %i\n", sum);
		wait(NULL);
	}

	return (0);
}