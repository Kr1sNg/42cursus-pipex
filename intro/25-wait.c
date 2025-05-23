/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25-wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 20:57:11 by tat-nguy         ###   ########.fr       */
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

return child's PID in success and return -1 if there's no child process to wait.
the waitpid can return 0 if WNOHANG option was chosen and if the child which it is
waiting for has not changed states yet.

wait() are doing is not only waiting for child processes to end,
but also get the exit code so the child process can be cleaned up properly

pid: the PID of child process we should wait for. As -1 is the parent process, indeed waitpid(-1, status, 0) is exactly the same
with wait(status).

options: waitpid offers several options. There's WNOHANG. With this option, waitpid returns
immediately if the child process has not ended yet. Without WNOHANG, the parent process will by
default remains suspended as long as the child is executing its tasks.

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int	main(int ac, char *av[])
{
	int pid1, pid2;

	pid1 = fork();
	if (pid1 == -1)
		return (-42);
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution pid1 %d\n", getpid());
		return 0;
	}
	else
	{
		printf("PID1: %d\n", pid1);
	}
	
	pid2 = fork();
	if (pid2 == -1)
		return (-42);
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution pid2 %d\n", getpid());
		return 0;
	}
	else
	{
		printf("PID2: %d\n", pid2);
	}

	// wait(NULL); // wait() could work properly here
	// wait(NULL);

	int pid1_res = waitpid(pid1, NULL, 0); // 0: how to wait
	printf("Waited for %d\n", pid1_res);
	int pid2_res = waitpid(pid2, NULL, 0);
	printf("Waited for %d\n", pid2_res);

	return (0);
}
