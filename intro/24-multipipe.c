/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22-child_sent_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/06 19:20:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* working with multiple pipes
	main: main send x to pid1
	pid1: recieve x from main, add +5 to x then send x to pid2
	pid2: recieve x from pid1, add +5 to x then sent to main

					 main
		fd[0][0]  /		  \  fd[0][1]
		fd[1][1] /		   \  fd[2][0]
			 pid1 >_________> pid2
				fd[1][0]  fd[2][1]

	*/
/* dup2(fd, fd2) duplicate fd to fd2, closing fd2 and making it open on the same file */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd[3][2];
	int i;
	for (i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) == -1)
			return (-42);
	}

	int	pid1 = fork();
	if (pid1 == -1)
		return (-42);
	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][0]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) == -1)
			return (-42);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) == -1)
			return (-42);
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}

	int	pid2 = fork();
	if (pid2 == -1)
		return (-42);
	if (pid2 == 0)
	{
		close(fd[1][1]);
		close(fd[0][0]);
		close(fd[2][0]);
		close(fd[0][1]);
		int x;
		if (read(fd[1][0], &x, sizeof(int)) == -1)
			return (-42);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) == -1)
			return (-42);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	// Parent process
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[2][1]);
	close(fd[1][1]);
	int x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("We start with x = %i\n", x);
	if (write(fd[0][1], &x, sizeof(int)) == -1)
		return (-42);
	if (read(fd[2][0], &x, sizeof(int)) == -1)
		return (-42);
	printf("Result after 2 pipes is: %i\n", x);
	close(fd[0][1]);
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
	  
}
