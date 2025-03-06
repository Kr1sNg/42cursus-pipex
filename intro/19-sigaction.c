/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-sigaction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:17 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* send signal to the terminal, ctr-Z can't stop the program */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigtstp(int sig)
{
	printf("Stop not allowed\n");
}

void handle_sigcont(int sig)
{
	printf("Input number: \n");
	fflush(stdout);
}

int	main(int ac, char *av[])
{
	struct sigaction sa;
		
	sa.sa_handler = &handle_sigcont;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCONT, &sa, NULL);

	// signal(SIGTSTP, &handle_sigtstp);
	
	int x;
	printf("input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x * 5);
	return (0);
}

// ps - to check which process is running
// pidof bash/zsh - to check no of this process