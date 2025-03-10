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

/* working with multiple forks and pipes
	if we create 'n' processes => 'n + 1' pipes
*/
/* dup2(fd, fd2) duplicate fd to fd2, closing fd2 and making it open on the same file */

/*		   main [m]pipe[3][0]
[m]pipe[0][1]⬇️
 [0]pipe[0][0]⬇️ [0]pipe[1][1]	[2]pipe[2][0] [2]pipe[3][1]
	process pid[0] w->->   pid[1]	w->	pid[2]
				[1]pipe[1][0]  [1]pip[2][1]   
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(int ac, char **av)
{
	int pids[PROCESS_NUM];
	int	pipes[PROCESS_NUM + 1][2]; //fd[0]: input et fd[1] out
	int i = 0;
	
	while (i < PROCESS_NUM + 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-42);
		i++;
	}

	for (i = 0; i < PROCESS_NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-42);
		if (pids[i] == 0) 
		{
			int j;
			for (j = 0; j < PROCESS_NUM + 1; j++)
			{
				if (i != i)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
			}
			int x;
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
				return (-42);
			printf("(%d) process got %d\n",getpid(), x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
				return (-42);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0); // if not this child process will create new forks...
		}
	}

	int y = 5;
	printf("Main process (%d) send %d\n", getpid(), y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
		return (-42);
	if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
		return (-42);
	printf("The final result is %d\n", y);
	close(pipes[0][1]);
	close(pipes[PROCESS_NUM][0]);

	for (i = 0; i < PROCESS_NUM; i++)
	{
		wait(NULL); // wait all child close
	}


	return (0);
	  
}
