/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23-pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/22 20:58:07 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* simulating the pipe '|' */

/*						main process
	ping -c 5 google.com	|		grep round-trip
			\>>stdout>>>>>>>pipe>>>stdin>>/
*/

/* dup2(fd, fd2) duplicate fd to fd2, closing fd2 and making it open on the same file */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd[2]; /* fd[0]: in - fd[1]: out */
	if (pipe(fd) == -1)
		return (-42);
	/* we need have 3 processes: main, ping and grep*/
	/* create process for ping */
	int pid_ping = fork();
	if (pid_ping == -1)
		return (-42);
	if (pid_ping == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO); // to write to the pipe
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
		close(fd[1]);
	}
	
	/* create process for grep */
	int	pid_grep = fork();
	if (pid_grep == -1)
		return (-42);
	if (pid_grep == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); // to read from pipe
		execlp("grep", "grep", "round-trip", NULL);
		close(fd[0]);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_ping, NULL, 0);
	waitpid(pid_grep, NULL, 0);

	return (0);
}
