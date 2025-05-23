/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25b-waitid-WIFSIGNALED.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 20:57:21 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 pid_t	wait(int *wstatus);
 pid_t	waitpid(pid_t pid, int *wstatus, int options);

'wstatus': a pointer to an integer type variable in which 'wait' and 'waitpid'
can store the child's exit status. We can examine this number with different 
macros to determine if the child finished normally or was interrupted:
	- WIFEXITED(status): returns true if the child terminated normally (by calling
	exit or finishing through the main function of program).
		- WEXITSTATUS(status): to be used only if WIFEXITED returned true.
		Returns the child’s exit code, meaning the number the child specified
		to the exit function or in the main function’s return.
	- WIFSIGNALED(status): return true if the child was forcefully terminated
	by a signal (like SIGKILL, SIGTERM)
		- WTERMSIG(status): to be used only if WIFSIGNALED returned true.
		Returns the signal number that provoked the child’s termination.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void	child_routine(void)
{
	printf("\e[36mChild: Hi, I'm the child in an infinite loop.\e[0m\n");
	while (1)
		continue ;
}

void	kill_and_get_children(pid_t *pid)
{
	int	status;
	int	i;

	printf("Parent: I'm the murderous parent.\n");
	i = 0;
	while (i < 3) // kill all 3 childs with a signal
	{
		kill(pid[i], SIGTERM);
		i++;
	}
	printf("Parent: I killed all 3 child processes. Muahahaha\n");
	i = 0;
	while (i < 3) // wait for each child and get its exit status
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			printf("Parent: Child [%d] terminated normally.\n", pid[i]);
		else if (WIFSIGNALED(status))
		{
			printf("Parent: Child [%d] was interrupted by signal.\n", pid[i]);
			if (WTERMSIG(status) == SIGTERM)
				printf("\e[31mParent: Child [%d] got the %d signal, SIGTERM\e[0m\n",
                            pid[i], WTERMSIG(status));
			if (WTERMSIG(status) == SIGKILL)
				printf("\e[31mParent: Child [%d] got the %d signal, SIGKILL\e[0m\n",
                            pid[i], WTERMSIG(status));
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	pid_t pid[3];
	int	i = 0;

	while (i < 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
			child_routine();
		else
			printf("Parent: Child #%d created with pid = %d\n", i, pid[i]);
		usleep(1000); //Delay next child's creation
		i++;
	}
	kill_and_get_children(pid);
	return (EXIT_SUCCESS);
}
