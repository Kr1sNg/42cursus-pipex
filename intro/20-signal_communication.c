/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20-signal_communication.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/06 16:56:43 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* send signal to the terminal, ctr-Z can't stop the program */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 0;

void handler_sigusr1(int sig)
{
	if (x == 0)
		printf("\n(HINT) Remember that multiplication is repetitive addition\n");
}

int	main(int ac, char *av[])
{
	int pid = fork();
	if (pid == -1)
		return (-42);
	
	if (pid == 0)
	{
		sleep(5);
		kill(getppid(), SIGUSR1);
		
	}
	else
	{
		struct sigaction sa = {0};
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handler_sigusr1;
		sigaction(SIGUSR1, &sa, NULL);
		
		printf("What is the result of 3 x 5? ");
		scanf("%d", &x);
		if (x == 15)
			printf("Right!\n");
		else
			printf("Wrong!\n");
		wait(NULL);
	}
	return (0);
}

// ps - to check which process is running
// pidof bash/zsh - to check no of this process