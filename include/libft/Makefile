# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 13:31:06 by amezoe            #+#    #+#              #
#    Updated: 2024/11/24 15:12:41 by amezoe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c ft_strlen.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_striteri.c \
					ft_memmove.c ft_putnbr_fd.c  ft_putstr_fd.c ft_putendl_fd.c ft_strrchr.c \
					ft_toupper.c ft_strdup.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					  ft_strjoin.c ft_strmapi.c ft_strtrim.c  ft_split.c
OBJS			= $(SRCS:.c=.o)

INCLUDES	= -I includes

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re