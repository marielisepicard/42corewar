# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/19 11:32:25 by agelloz           #+#    #+#              #
#    Updated: 2020/02/13 22:18:17 by ekelkel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

ASM = asm
COR = corewar
LIB = libft/libft.a

IFLAGS = -I inc -I libft/inc
CFLAGS = -g3 -Wall -Wextra -Werror

OPATH_ASM = obj_asm/
OPATH_COR = obj_cor/

INC_ASM += op.h asm.h
INC_COR += corewar.h

SRC_ASM += asm.c
SRC_ASM += lexing.c
SRC_ASM += lexing_line.c
SRC_ASM += lexing_tools.c
SRC_ASM += parsing.c
SRC_ASM += parsing_header.c
SRC_ASM += parsing_instruction.c
SRC_ASM += parsing_tools.c
SRC_ASM += parsing_tools2.c
SRC_ASM += output.c
SRC_ASM += free.c
SRC_ASM += exit_asm.c
SRC_ASM += exit_asm2.c

SRC_COR += virtualmachine.c
SRC_COR += init_vm.c
SRC_COR += parsing_champions.c
SRC_COR += parsing_options.c
SRC_COR += parsing_args.c
SRC_COR += init_players_processes.c
SRC_COR += launch_fight.c
SRC_COR += manipulate_cycles.c

SRC_COR += tools.c
SRC_COR += op_sub.c
SRC_COR += bite_op_utils.c
SRC_COR += bite_op.c
SRC_COR += op_add.c
SRC_COR += op_ld.c
SRC_COR += convert_dir_ind.c
SRC_COR += op_sti_utils.c
SRC_COR += op_sti.c
SRC_COR += op_st.c
SRC_COR += op_live.c
SRC_COR += op_aff.c
SRC_COR += op_fork.c
SRC_COR += op_zjmp.c
SRC_COR += op_lldi.c
SRC_COR += op_ldi.c
SRC_COR += monitor_lives.c
SRC_COR += monitor_lives2.c
SRC_COR += dump_arena.c
SRC_COR += visualizer.c
SRC_COR += init_visu.c
SRC_COR += execute_visu.c
SRC_COR += reload_visu.c
SRC_COR += exit_vm.c
SRC_COR += debug_print.c
SRC_COR += op_and.c
SRC_COR += op_and2.c
SRC_COR += ft_itobin.c
SRC_COR += op_lld.c
SRC_COR += option_v.c
SRC_COR += load_op.c

OBJ_ASM = $(patsubst %.c, $(OPATH_ASM)%.o, $(SRC_ASM))
OBJ_COR = $(patsubst %.c, $(OPATH_COR)%.o, $(SRC_COR))

vpath	%.c src/asm/
vpath	%.c src/corewar/
vpath	%.h inc/
vpath	%.h libft/inc/

all: $(LIB) $(ASM) $(COR)

debug: fclean
	$(MAKE) -C libft debug
	$(MAKE) $(MAKEFILE) CFLAGS="-Wall -Wextra -g3 -fsanitize=address,undefined -Wpadded"

$(ASM): $(LIB) $(OPATH_ASM) $(OBJ_ASM) $(INC_ASM)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJ_ASM) $<
	printf "\r\33[2K\r$(GREEN)created: $@$(NC)\n"

$(COR): $(LIB) $(OPATH_COR) $(OBJ_COR) $(INC_COR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJ_COR) $< -lncurses
	printf "\r\33[2K\r$(GREEN)created: $@$(NC)\n"

$(LIB): FORCE
	$(MAKE) -C libft

FORCE:

$(OBJ_ASM): $(OPATH_ASM)%.o : %.c $(INC_ASM)
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@
	printf "\33[2K\r$(CYAN)compiling: $<$(NC)"

$(OBJ_COR): $(OPATH_COR)%.o : %.c $(INC_COR)
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@
	printf "\33[2K\r$(CYAN)compiling: $<$(NC)"

$(OPATH_COR):
	mkdir -p $@

$(OPATH_ASM):
	mkdir -p $@

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ)
	rm -rf $(OPATH_ASM)
	rm -rf $(OPATH_COR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -rf $(ASM)
	rm -rf $(COR)
	echo "$(RED)deleted: $(ASM)$(NC)"
	echo "$(RED)deleted: $(COR)$(NC)"

re: fclean all

NC=\033[0m
RED=\033[0;31m
GREEN =\033[32m
CYAN=\033[0;36m

.PHONY: all clean fclean debug
.SILENT:
