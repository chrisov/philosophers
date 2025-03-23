#
#
CC = cc
CFLAGS = -g -pthread -Wall -Werror -Wextra -I$(INCDIR)
MAKEFLAGS += -s

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include

SRCS = $(SRCDIR)/main.c $(SRCDIR)/functions.c $(SRCDIR)/table.c\
		$(SRCDIR)/routine.c $(SRCDIR)/more_functions.c $(SRCDIR)/params.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "\033[33mCompilating...\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Compilation \033[32msuccessful\033[0m!"
	@echo "eg: ./$(NAME) [num_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] (OPTIONAL)[num_of_eat_times]"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	@echo "\033[33mCleaning up build and library files...\033[0m"
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)
	@echo "All build files cleaned up \033[32msuccessfully\033[0m!"

fclean: clean
	clear
	@echo "\033[33mCleaning up executables and static libraries...\033[0m"
	rm -f $(NAME)
	@echo "Executables and static libraries cleaned up \033[32msuccessfully\033[0m!"
	
re: fclean all

.PHONY: all clean fclean re