NAME			= nikkishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I$(LIBFT_DIR)

INC_DIR			= include/
LIBFT_DIR		= include/libft/

LIBFT			= $(LIBFT_DIR)libft.a


# Source files for minishell

#MINISHELL_SRCS_ALICIA = 


#MINISHELL_SRCS_SOPHIA = 



#---------------WILL HAVE TO ADD ASCII ART FOR NIKKISHELL---------------


MINISHELL_OBJS	= $(MINISHELL_SRCS_ALICIA:.c=.o) $(MINISHELL_SRCS_SOPHIA:.c=.o)

all:			$(NAME)

$(NAME):		$(MINISHELL_OBJS) $(LIBFT_DIR)/libft.a
				$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBS) -o $(NAME)
	
libft/libft.a:	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				rm -f $(MINISHELL_OBJS)

fclean:			clean
				$(MAKE) -C $(LIBFT_DIR) fclean
				rm -f $(NAME)

re:				fclean all

# valgrind rule
valgrind:		$(NAME)
				valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)

.PHONY:			all libft clean fclean re