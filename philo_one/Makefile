# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lryst <lryst@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/07 19:10:00 by lryst             #+#    #+#              #
#    Updated: 2021/03/17 12:18:27 by lryst            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
#HEAD := -I./includes/ -I./libft/includes
HEAD := -I./includes/

CFLAGS = -Wall -Wextra -Werror -pthread
CFLAGSF = -g3 -Wall -Wextra -Werror -pthread


SRC := \
	init.c \
	main.c \
	philo_actions.c \
	philo_routine.c \
	utils.c \

OBJS = $(addprefix objs/, $(SRC:.c=.o))
#color
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef


all: $(NAME)
#@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
$(NAME): $(OBJS)
	@echo ''
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME)
	@echo '	 '
	@echo '	......( \_/ ) '
	@echo '	......( o_o ) '
	@echo '	..../""""""""""""\======░ ▒▓▓█D' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";
	@echo '	/"""""""""""""""""""\ '
	@echo '	\_@_@_@_@_@_@_@_@_@_/'

objs/%.o: %.c
	@mkdir -p $(dir $@)
	@$(call run_and_test,gcc $(CFLAGS) $(HEAD) -c $< -o $@)

clean:
	@rm -rf $(OBJS) objs
	@printf "%b" "$(ERROR_COLOR)\tmake clean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";
#	@make 42

fclean:
	@rm -rf $(NAME) $(OBJS) objs
	@printf "%b" "$(ERROR_COLOR)\tmake fclean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";

re: fclean all

#@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
cn: $(OBJS)
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME)
	@echo 'simple ' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";


#@gcc $(CFLAGSF) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
cs: $(OBJS)
	@gcc $(CFLAGSF) $(HEAD) $(OBJS) -o $(NAME)
	@echo 'sanitize' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";

leaks:
	leaks $(NAME)

norme:
	@norminette *.*
