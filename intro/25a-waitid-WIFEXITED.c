/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25a-waitid-WIFEXITED.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 10:24:41 by tat-nguy         ###   ########.fr       */
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
		- WEXITSTATUS(status): to be used only if WIFEXITED returned TRUE.
		Returns the child’s exit code, meaning the number the child specified
		to the exit function or in the main function’s return.
	- WIFSIGNALED(status): return true if the child was forcefully terminated
	by a signal (like SIGKILL, SIGTERM)
		- WTERMSIG(status): to be used only if WIFSIGNALED returned TRUE.
		Returns the signal number that provoked the child’s termination.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef CHILD_EXIT
# define CHILD_EXIT 42
#endif

#define EXPECTED 42

void	child_routine(pid_t pid)
{
	printf("\e[36mChild: Hi, I'm the child. PID received from fork = %d\e[0m\n", pid);
	printf("\e[36mChild: Exiting with exit code %d.\e[0m\n", CHILD_EXIT);
	exit(CHILD_EXIT);
}

void	parent_routine(pid_t pid)
{
	int	status;

	printf("Parent: I'm parent. PID recieved from fork = %d\n", pid);
	printf("Parent: Waiting for my child with PID [%d]\n", pid);
	waitpid(pid, &status, 0);
	printf("Parent: My child is exited with status %d\n", status);
	if (WIFEXITED(status)) // if my child exited normally (not by signal)
	{
		printf("Parent: My child's exit code is %d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == EXPECTED)
			printf("Parent: That's what we expected!\n");
		else
			printf("Parent: Sorry! Not what we expected...\n");
	}
}

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // child process
		child_routine(pid);
	else
		parent_routine(pid);
	return (EXIT_SUCCESS);
}
