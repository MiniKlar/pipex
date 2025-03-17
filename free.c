/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:15:04 by lomont            #+#    #+#             */
/*   Updated: 2025/03/17 23:47:57 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_close(t_data *data)
{
	// close(data->fdpipe[0]);
	// close(data->fdpipe[1]);
	close(data->out_fd);
	close(data->fd);
	free_tab(data->command_arg);
	free_tab(data->command_arg_2);
	free(data);
}

void fork_error(int nb_fork, t_data *data)
{
	if (nb_fork == 1)
	{
		if (data->id_fork == -1)
		{
			perror("1st Fork failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (data->id_fork2 == -1)
		{
			perror("2st Fork failed");
			exit(EXIT_FAILURE);
		}
	}
}
