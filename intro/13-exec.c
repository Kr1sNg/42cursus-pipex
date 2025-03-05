/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 18:24:04 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exec creates new process totally replaces main process then executes
it closes all (also the main process) when finishing */
/* so idea is create fork inside child to run exec,
when it terminates, it doesn't matter to main process */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	main(int ac, char *av[], char **env)
{
	//execlp("ping", "ping", "google.com", NULL); // l: list, p: path
	
	char *arr[] = {"/bin/ping", "google.com", NULL};

	// we can find ping in /bin/
	execve("/bin/ping", arr, env); // v: vector to path, e: environment

	int err = errno;
	printf("error no: %i\n", err);
	
	return (0);
}

