/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:58 by lomont            #+#    #+#             */
/*   Updated: 2025/03/23 17:40:59 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../LIB_C/LIB_C.h"
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	char	**command_arg;
	char	**command_arg_2;
	int		fdpipe[2];
	pid_t	id_fork;
	pid_t	id_fork2;
}				t_data;

t_data	*initialise_data(void);
void	free_close(t_data *data);
void	free_tab(char **tab);
char	*check_command_path(char *command, char **envp);
char	*new_command_function(char **path, char *new_command);
char	*recup_env(char **envp);
int		fork_pipex(t_data *data, char **argv, int argc, char **envp);
void	fork_pipex1(t_data *data, char **argv, char **envp);
void	fork_pipex2(t_data *data, char **argv, int argc, char **envp);
int		pipex(int argc, char **argv, char **envp);
void	fork_error(int nb_fork, t_data *data);
int		ft_wait(t_data *data, int wstatus);
int		open_access_infile(t_data *data, char *argv);

#endif
