/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:58 by lomont            #+#    #+#             */
/*   Updated: 2025/03/17 23:45:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./LIB_C/LIB_C.h"
# include <sys/wait.h>

typedef struct s_data
{
	char	**command_arg;
	char	**command_arg_2;
	int		fd;
	int		out_fd;
	int		fdpipe[2];
	pid_t	id_fork;
	pid_t	id_fork2;
}				t_data;

t_data	*initialise_data(void);
void	free_close(t_data *data);
void	free_tab(char **tab);
char	*check_command_path(char *command, char **envp);
//char	*find_env(void);
char	*decoup_env(char **envp);
void	fork_pipex(t_data *data, char **envp);
void	fork_pipex1(t_data *data, char **envp);
void	fork_pipex2(t_data *data, char **envp);
int		pipex(int argc, char **argv, char **envp);
void	fork_error(int nb_fork, t_data *data);
#endif
