/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/19 05:56:50 by lomont           ###   ########.fr       */
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

// quand le infile ne peut pas etre open, la commande du out doit quand meme se faire et vice versa
// env -i time valgrind --track-fds=yes --trace-children=yes  --leak-check=full  --show-leak-kinds=all ./pipex infile "sleep 2" "sleep 5" jesuila
// leaks de fd et checker si la commande est F_OK puis X_OK avant de checker le path car ca peut etre un path absolu


// /usr/bin/ls

// F OK

// cmd not found

//X OK

// permission denied

