/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 20:55:36 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
wait(), waitpid() wait for process to change state.

wait() suspends execution of the calling thread until
one of its children terminates.

waitpid() suspends execution of the calling thread until in a child specified
by pid has changed states, which are: the child terminated,
the child was stopped by a signal, the child was resumed by a signal.

 pid_t	wait(int *wstatus);
 pid_t	waitpid(pid_t pid, int *wstatus, int options);

return 0 in success and return -1 if there's no child process to wait.

wait() are doing is not only waiting for child processes to end,
but also get the exit code so the child process can be cleaned up properly

*/

/* print 0-10 with 0-5 from child process and 6-10 from main process*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int ac, char *av[])
{
	int id = fork();
	int n;

	if (id == 0)
		n = 1;
	else
		n = 6;

	if (id != 0)
		wait(NULL); // main process will wait for child process to finish executing
	int i;
	for(i = n; i < n + 5; i++)
	{
		printf("%i ", i);
		fflush(stdout);
	} 
	if (id != 0)
		printf("\n");
	return (0);
}
