/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpushkar <vpushkar@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:46 by vpushkar          #+#    #+#             */
/*   Updated: 2025/05/12 15:56:55 by vpushkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/**
 * @brief Signal handler for incoming confirmation signal.
 *
 * Handles SIGUSR1 signal, prints a confirmation message and exits
 * the program.
 *
 * @param signum The received signal number.
 * @param siginf Signal information (unused).
 * @param rest Additional context info (unused).
 */
static void	handler(int signum, siginfo_t *siginf, void *rest)
{
	(void)siginf;
	(void)rest;
	if (signum == SIGUSR1)
	{
		ft_printf("Signal received.\n");
	}
	exit(0);
}

/**
 * @brief Sends a string to another process using signals.
 *
 * Each character is sent bit by bit to the given PID. A null
 * character is sent at the end to indicate the end of the string.
 *
 * @param str The string to send.
 * @param pid The PID of the target process.
 */
static void	ft_encrypt_and_send(char *str, int pid)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		i = 7;
		while (i >= 0)
		{
			if (((str[j] >> i) & 1) == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(50);
			i--;
		}
		j++;
	}
	i = 7;
	while (i >= 0)
	{
		kill(pid, SIGUSR1);
		usleep(50);
		i--;
	}
}

/**
 * @brief Entry point of the client program.
 *
 * Parses arguments, sets up signal handler, and sends the string to
 * the specified PID using ft_encrypt_and_send.
 *
 * @param ac Argument count.
 * @param av Argument vector: av[1] is PID, av[2] is the string.
 * @return int Exit status.
 */
int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	siga;

	if (ac != 3)
	{
		ft_printf("Wrong input.\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_printf("PID is wrong.");
		return (1);
	}
	siga.sa_sigaction = handler;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &siga, NULL);
	ft_encrypt_and_send(av[2], pid);
	pause();
	return (0);
}
