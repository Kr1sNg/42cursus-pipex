/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-signal_SIGCONT.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/06 13:52:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* print each one sec after 10s, terminate */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int	main(int ac, char *av[])
{
	int	pid = fork();
	if (pid == -1)
		return (-42);
	if (pid == 0)
	{
		while (1)
		{
			printf("Program is executing!\n");
			usleep(500000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		int t = 6;
		while (--t > 0)
		{
			printf("Time in seconds: %i\n", t);
			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(1);
			}
		}
		kill(pid, SIGKILL);
		wait(NULL);
		
	}
	return (0);
}

// ps - to check which process is running
// pidof bash/zsh - to check no of this process