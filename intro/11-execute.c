/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 16:29:51 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exec creates new process totally replaces main process then executes
it closes all (also the main process) when finishing */
/* so idea is create fork inside child to run exec,
when it terminates, it doesn't matter to main process */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int	main(int ac, char *av[])
{
	int	pid = fork();
	if (pid == -1)
		return (-42);
	if (pid == 0)
	{
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
		printf("This line should not print on the terminal because execlp \
		already terminates the child process before this!\n");
	}
	else
	{
		wait(NULL);
		printf("Success!\n");
	}
	return (0);
}

