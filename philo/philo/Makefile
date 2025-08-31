NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude
LDFLAGS		= -pthread

SRCDIR		= src
OBJDIR		= obj

SRCS		= main.c \
			  dinner.c \
			  dinner_utils.c \
			  utils.c \
			  init.c \
			  manager.c \
			  monitor.c \
			  validation.c \
			  actions.c \
			  fork_utils.c

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c include/philo.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
