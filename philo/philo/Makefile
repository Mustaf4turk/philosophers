NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -g
LDFLAGS = -pthread

SRCDIR  = src
OBJDIR  = obj

SRC     = main.c \
          dinner.c \
          dinner_utils.c \
          utils.c \
          init.c \
          manager.c \
          monitor.c \
          validation.c \
          actions.c

OBJ     = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c include/philo.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
