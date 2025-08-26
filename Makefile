NAME			= nikkishell
CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LIBFT_DIR)

INC_DIR			= include/
LIBFT_DIR		= include/libft/


LIBFT			= $(LIBFT_DIR)libft.a

READLINE_FLAGS  = -lreadline

# --- Source Files ---
SRCS_NAMES      = \
	tester.c \
	free.c \
	free1.c \
	signals.c \
	tokenize_utils.c \
	tokenize_utils1.c \
	tokenize.c \
	env_utils.c \
	parser_utils.c \
	parser.c \
	exec.c	\
	exec_utils.c \
	exec_path.c	\
	exec_pipes.c	\
	exec_builtins.c	\
	redirs.c	\
	heredoc.c	\
	cd.c		\
	cd_utils.c	\
	echo.c		\
	pwd.c		\
	env.c		\
	unset.c		\
	export.c	\
	export_utils.c	\
	export_utils2.c	\
	exit.c		\
	parent.c	\
	env_update.c \
	expansion.c	\
	parent.c	\
	env_update.c \
	basic.c \
	basic1.c \

MINISHELL_SRCS  = $(addprefix src/, $(SRCS_NAMES))

MINISHELL_OBJS  = $(MINISHELL_SRCS:.c=.o)

# --- Main Targets ---
all:            $(NAME)

$(NAME):		$(MINISHELL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) include/libft/libft.a $(READLINE_FLAGS) -o $(NAME)

#--------UNDER THE MAIN TARGETS IT ONLY COMPILES IF IT IS WITH----------------------------------
#--------INCLUDE/LIBFT/LIBFT.A I BEG YOU DONT CHANGE IT IT DOESNT WORK------------------

$(LIBFT):
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning project object files..."
	rm -f $(MINISHELL_OBJS)
	@echo "Cleaning libft object files..."
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:         clean
	@echo "Cleaning executable..."
	rm -f $(NAME)
	@echo "Cleaning libft executable/archive..."
	$(MAKE) -C $(LIBFT_DIR) fclean

re:             fclean all

valgrind:       $(NAME)
	@echo "Running Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY:         all clean fclean re valgrind