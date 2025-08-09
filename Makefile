#
#
CC = cc
CFLAGS = -g -pthread -Wall -Werror -Wextra -I$(INCDIR)
MAKEFLAGS += -s

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include

SRCS = $(SRCDIR)/main.c $(SRCDIR)/functions.c $(SRCDIR)/table.c \
		$(SRCDIR)/routine.c $(SRCDIR)/more_functions.c $(SRCDIR)/utils.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@printf "[.]   📦 Compiling '\033[33m$(NAME)\033[0m'...\r"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "🚀 '\033[33m$(NAME)\033[0m' compiled \033[32msuccessfully\033[0m!"
	@echo "\neg: ./$(NAME) [num_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_eat_times](OPT)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)

fclean: clean
	@printf "[.]   🧹 Removing '\033[33m$(NAME)\033[0m' build...\r"
	rm -f $(NAME)
	printf "[✅]  🧹 Removed '\033[33m$(NAME)\033[0m' build...  \n"

re: fclean all

.PHONY: all clean fclean re
