# For compilers to find readline you may need to set:
# export LDFLAGS="-L/Users/vroch/.brew/opt/readline/lib"
# export CPPFLAGS="-I/Users/vroch/.brew/opt/readline/include"

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

#for Mac M1 or not
ifeq ($(shell uname -m), arm64)
INC = -I inc -I src/libft/inc -I/opt/homebrew/opt/readline/include/readline
LFT = -L src/libft -lft
READLINE = -L/opt/homebrew/opt/readline/lib
else
INC = -I inc -I src/libft/inc -I$(HOME)/.brew/opt/readline/include
LFT = -L src/libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib
endif

SRC_NAME = 	minishell.c \
			ms_builtins.c \
			ms_b_echo.c \
			ms_b_echo_print.c \
			ms_b_echo_utils.c \
			ms_b_tabs.c \
			ms_b_tabs_utils.c \
			ms_b_tabsort.c \
			ms_b_variables.c \
			ms_b_var_utils.c \
			ms_b_export.c \
			ms_b_export_utils.c \
			ms_b_export_vars.c \
			ms_b_unset.c \
			ms_b_cd.c \
			ms_b_pwd.c \
			ms_b_other_launch.c \
			ms_b_other_utils.c \
			ms_b_exit.c \
			ms_b_exit_utils.c \
			ms_signals.c \
			ms_parsing.c \
			ms_p_master.c \
			ms_p_count.c \
			ms_p_monitor_quotes.c \
			ms_p_pipes.c \
			ms_p_pipes_utils.c \
			ms_p_pipes_quotes.c \
			ms_p_stock.c \
			ms_p_howmany.c \
			ms_p_quotes.c \
			ms_p_utils.c \
			ms_pipes.c \
			ms_pipes_loops.c \
			ms_pipes_utils.c \
			ms_redirections.c \
			ms_r_check.c \
			ms_r_cmds_s_cmd.c \
			ms_r_cmds_s_redir.c \
			ms_r_cmds_split.c \
			ms_r_cmds.c \
			ms_r_doors.c \
			ms_r_files.c \
			ms_r_heredoc_utils.c \
			ms_r_heredoc.c \
			ms_r_launch_p.c \
			ms_r_launch_utils.c \
			ms_r_launching.c \
			ms_r_launch.c \
			ms_r_parsing.c \
			ms_r_set_in_p.c \
			ms_r_set_in_p_utils.c \
			ms_r_set_utils.c \
			ms_r_set.c \
			ms_r_utils.c \
			ms_free.c \
			ms_free_utils.c \
			ms_utils.c \
			ms_errors.c


OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = src/libft/
SRC_DIR = src/
OBJ_DIR = obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent 
	@gcc -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft -lreadline $(READLINE)
	@echo "##### minishell compiling finished! #####"
	@echo "   (¯\`v´¯)"
	@echo "  (¯\`(█)´¯)  (¯\`v´¯)"
	@echo "   (_.^._)  (¯\`(█)´¯)"
	@echo "     (¯\`v´¯)´(_.^._)"
	@echo "    (¯\`(█)´¯)(¯\`v´¯)"
	@echo "     (_.^._)(¯\`(█)´¯)"
	@echo " (¯\`v´¯)     (_.^._)"
	@echo "(¯\`(█)´¯) "
	@echo " (_.^._)  FLOWERS Team"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c $< $(INC) 

run:
	./$(NAME)

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -f $(OBJ)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@rm -f $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re run
