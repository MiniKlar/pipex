/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/23 17:24:08 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
