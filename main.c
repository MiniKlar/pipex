/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/15 01:07:18 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 5)
	{
		if (access(argv[1], F_OK | R_OK) != 0)
		{
			perror("File not accessible");
			exit(EXIT_FAILURE);
		}
		data = initialise_data();
		if (access(argv[argc - 1], F_OK | W_OK) == 0)
		{
			data->out_fd = open(argv[argc - 1], O_RDWR, 0755);
		}
		else
		{
			perror("Output file does not exist");
			exit(EXIT_FAILURE);
		}
		data->command_arg = ft_split(argv[2], ' ');
		data->command_arg_2 = ft_split(argv[3], ' ');
		data->new_pathcommand = check_command_path(data->command_arg[0]);
		data->new_pathcommand_2 = check_command_path(data->command_arg_2[0]);
		data->fd = open(argv[1], O_RDWR);
		pipe(data->fdpipe);
		fork_pipex(data);
		return (0);
	}
}
