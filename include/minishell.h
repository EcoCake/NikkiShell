/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:31:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/08/28 17:51:25 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIHISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "functions.h"
# include "libft/libft.h"


#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500


# endif