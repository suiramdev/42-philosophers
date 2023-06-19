# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 22:19:57 by mnouchet          #+#    #+#              #
#    Updated: 2023/06/08 21:16:43 by mnouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

## ########################################################################## ##
#	INGREDIENTS																# ##
## ########################################################################## ##
# INCS			header file locations
#
# SRCS_DIR		source directory
# SRCS			source files
#
# BUILD_DIR		build directory
# OBJS			object files
#
# CC			compiler
# CFLAGS		compiler flags
# CPPFLAGS		preprocessor flags

INCS		:= includes

SRCS_DIR	:= src
SRCS		:= main.c					\
			   routine/philosopher.c	\
			   routine/supervisor.c		\
			   types/philosopher.c		\
			   types/table.c			\
			   utils/log.c				\
			   utils/string.c			\
			   utils/time.c

SRCS		:= $(SRCS:%=$(SRCS_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)

CC			:= cc
CFLAGS		:= -g3 -Wall -Wextra -Werror
CPPFLAGS    := $(INCS:%=-I%)

## ########################################################################## ##
#   UTENSILS																  ##
## ########################################################################## ##
# RM			force remove
# MAKEFLAGS		make flags
# DIR_UP		duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

## ########################################################################## ##
#   RECIPES																	  ##
## ########################################################################## ##
# all			default goal
# $(NAME)		link .o -> archive
# %.o			compilation .c -> .o
# clean			remove .o
# fclean		remove .o + binary
# re			remake default goal

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	echo "→ Compiling $<"
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	echo "\033[0;32m✓ $@ READY\033[0m"

clean:
	echo "→ Removing objects"
	$(RM) $(OBJS)

fclean: clean
	echo "→ Removing binaries"
	$(RM) $(NAME)

re: fclean all

.PHONY: re
