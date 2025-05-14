/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpushkar <vpushkar@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:47 by vpushkar          #+#    #+#             */
/*   Updated: 2025/05/12 15:58:16 by vpushkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/**
 * @brief Signal handler to receive and decode bits into characters.
 *
 * Accumulates bits sent via SIGUSR1 and SIGUSR2 into characters,
 * stores them in a buffer, and prints the full message once a null
 * terminator is received. Sends confirmation signal back to sender.
 *
 * @param signum The received signal number (SIGUSR1 or SIGUSR2).
 * @param siginf Signal info, used to get sender's PID.
 * @param rest Unused execution context pointer.
 */
static void	handler(int signum, siginfo_t *siginf, void *rest)
{
	static int				bit_index = 0;
	static unsigned char	current_char = 0;
	static char				buffer[BUFFER_SIZE];
	static int				buffer_index = 0;

	(void)rest;
	current_char <<= 1;
	if (signum == SIGUSR2)
		current_char |= 1;
	bit_index++;
	if (bit_index == 8)
	{
		buffer[buffer_index++] = current_char;
		if (current_char == '\0')
		{
			write(1, buffer, buffer_index);
			write(1, "\n", 1);
			kill(siginf->si_pid, SIGUSR1);
			buffer_index = 0;
		}
		bit_index = 0;
		current_char = 0;
	}
}

/**
 * @brief Entry point of the server program.
 *
 * Prints the current PID and sets up signal handlers for SIGUSR1 and
 * SIGUSR2 to receive data. Waits for signals in an infinite loop.
 *
 * @return int Always returns 0.
 */
int	main(void)
{
	pid_t				pid;
	struct sigaction	siga;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	siga.sa_sigaction = handler;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
