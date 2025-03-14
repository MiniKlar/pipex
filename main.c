/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/14 21:08:34 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = initialise_data();
	data->command_arg = ft_split(argv[2], ' ');
	data->command_arg_2 = ft_split(argv[3], ' ');
	if (access(argv[1], F_OK | R_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	data->new_pathcommand = check_command_path(data->command_arg[0]);
	data->new_pathcommand_2 = check_command_path(data->command_arg_2[0]);
	pipe(data->fdpipe);
	data->fd = open(argv[1], O_RDWR);
	if (access(data->new_pathcommand, F_OK) == 0)
	{
		unlink(argv[argc - 1]);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	data->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0755);
	fork_pipex(data);
}
