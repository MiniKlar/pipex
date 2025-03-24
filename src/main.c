/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/24 20:47:19 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_access_outfile(t_data *data, char *argv)
{
	int	fd;

	fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		free_close(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		exit(pipex(argc, argv, envp));
	else if (argc > 5)
	{
		ft_printf("Too much arguments\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_printf("Not enough arguments\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
