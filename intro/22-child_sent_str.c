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

/* send str from child back to parent */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

/* 1- user input str in child process
	2 - child send back str to parent
	3 - parent print out str */

int main(int ac, char **av)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (-42);
	
	int pid = fork();
	if (pid == -1)
		return (-42);
	
	if (pid == 0)
	{
		close(fd[0]); // we send from child back to parent so we don't need input
		char str[200];
		printf("Input string: ");
		fgets(str, 200, stdin);
		int len = strlen(str);
		str[len - 1] = '\0';
		if (write(fd[1], &len, sizeof(int)) == -1) // need to send len of str first!!!
			return (-42);
		
		if (write(fd[1], str, len) == -1)
			return (-42);

		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		char str[200];
		int len;
		if (read(fd[0], &len, sizeof(len)) == -1) // receive len of string
			return (-42);
		if (read(fd[0], str, len) == -1)
			return (-42);
		printf("Received in parent: [%s]\n", str);

		close(fd[0]);
		wait(NULL);
	}

	return (0);
}