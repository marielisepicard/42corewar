/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manki <manki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:48:02 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/14 09:17:32 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <errno.h>
# include <ncurses.h>

# define ERROR_MALLOC		"ERROR: malloc failed"
# define ERROR_OPEN_FILE	"ERROR: cannot open file"
# define ERROR_READ_FILE	"ERROR: cannot read file"
# define WRONG_EXTENSION	"ERROR: wrong file extension"
# define ERROR_FILE_SIZE	"ERROR: file is too big"

# define CODE_TOO_LARGE		0x00
# define CODE_TOO_SMALL		0x01
# define CODE_SIZE_DIFF		0x02

# define ARENA_LINE_SIZE 	64

# define SLEEP_TIME			2500

# define _GREY 				"\033[30m"
# define _RED 				"\033[31m"
# define _GREEN 			"\033[32m"
# define _YELLOW 			"\033[33m"
# define _BLUE 				"\033[34m"
# define _PURPLE 			"\033[35m"
# define _CYAN 				"\033[36m"
# define _WHITE 			"\033[37m"
# define _END 				"\033[0m"

# define OPTION_V_SIZE 		7
# define _REG 				"01"
# define _DIR 				"10"
# define _IND 				"11"

typedef enum		e_operations
{
	NO_OP, LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP,
	LDI, STI, FORK, LLD, LLDI, LFORK, AFF
}					t_operations;

typedef struct		s_player
{
	char	*file;
	char	*path;
	int		code_size;
	int		number;
	int		color;
	int		lives;
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH + 1];
	char	code[CHAMP_MAX_SIZE + 1];
	char	id;
	char	pad[2];
}					t_player;

typedef struct		s_dead_process
{
	int						number;
	int						cycles;
	struct s_dead_process	*next;
}					t_dead_process;

typedef struct		s_process
{
	char				*name;
	int					color;
	int					number;
	int					program_counter;
	int					tmp_program_counter;
	int					registers[REG_NUMBER];
	int					running;
	int					over;
	int					is_fork;
	int					alive;
	int					live_calls;
	int					since_last_live;
	int					cycles_to_wait;
	char				carry;
	char				pad[3];
	struct s_process	*next;
}					t_process;

/*
** option_v[5] :
** [0] Show lives
** [1] Show cycles
** [2] Show operations (Params are NOT litteral ...)
** [3] Show deaths
** [4] Show PC movements (Except for jumps)
** [5] Color
*/

typedef struct		s_vm
{
	WINDOW			*visu_main;
	WINDOW			*visu_info;
	WINDOW			*notif;
	WINDOW			*main_border;
	WINDOW			*info_border;
	WINDOW			*notifs_border;
	char			*last_alive_name;
	char			**champion_files;
	t_process		*process_list;
	t_player		players[MAX_PLAYERS];
	int				tab_pow[8];
	int				arena_moves[MEM_SIZE];
	int				arena_owner[MEM_SIZE];
	int				code_sizes[MAX_PLAYERS];
	int				count_players;
	int				dump;
	int				last_alive_number;
	int				live_calls;
	int				cycles;
	int				cycle_to_die;
	int				delta_ctd;
	int				delta_ctd_copy;
	int				neg_ctd;
	int				check_number;
	int				reg_pos;
	int				last_process_number;
	int				valid;
	unsigned int	reg;
	unsigned int	cpt_notifs;
	unsigned int	usleep;
	char			buf[5];
	unsigned char	arena[MEM_SIZE];
	int8_t			option_v[OPTION_V_SIZE];
	int8_t			option_ncurse;
	char			ocp[4][3];
	char			pad[7];
}					t_vm;

void				initialize_vm(t_vm *vm, char **av);
void				set_tab_pow(t_vm *vm);
void				parse_args(int ac, char **av, t_vm *vm);
void				parse_option_ncurse(t_vm *vm, int *i);
void				parse_option_dump(t_vm *vm, int *i, char **av, int ac);
void				parse_option_v(t_vm *vm, int *i, char **av);
void				parse_champions(t_vm *vm, int file_max_size);
void				init_players_processes(t_vm *vm);

void				launch_fight(t_vm *vm);
int					launch_add(t_vm *vm, t_process *process);
int					launch_sub(t_vm *vm, t_process *process);
int					launch_st(t_vm *vm, t_process *process);
int					set_pc_position(t_vm *vm, t_process *process, int pos);
void				set_colors(t_vm *vm, t_process *process, int res);
int					set_param2_utils(t_vm *vm, int pc, int param2);
int					set_param2(t_vm *vm, t_process *process);
int					set_param3(t_vm *vm, t_process *process);
int					launch_sti(t_vm *vm, t_process *process);
int					launch_ldi(t_vm *vm, t_process *process);
int					launch_lldi(t_vm *vm, t_process *process);
int					launch_ld(t_vm *vm, t_process *process);
int					launch_ldi_lldi(t_vm *vm, t_process *process);
int					op_live(t_vm *vm, t_process *process);
int					op_zjmp(t_vm *vm, t_process *process);
int					op_aff(t_vm *vm, t_process *process);
int					op_fork(t_vm *vm, t_process *process);
int					bite_op(t_vm *vm, t_process *process);
int					get_value1(t_vm *vm, t_process *p);
int					get_value2(t_vm *vm, t_process *p);
unsigned int		convert_dir(t_vm *vm, int index);
unsigned int		convert_ind(t_vm *vm, int index, int pc);
int					get_cycle_to_wait(int op);
char				check_reg(int reg);
int					get_new_position(t_vm *vm, int pc, int pos);
int					check_valid_reg(t_vm *vm, t_process *p);
void				restore_live_calls(t_process *list);
void				kill_dead_cursors(t_vm *vm);
int					count_live_calls(t_process *list);
void				dump_arena(t_vm *vm);
void				init_ncurse(t_vm *vm);
void				get_color(t_vm *vm, int *color, int on);
void				get_key(void);
void				reload_windows(t_vm *vm, int nb);
void				color_arena(t_vm *vm, t_process *process, int pc,
								char *sub_reg);
void				print_champ_infos(t_vm *vm);
void				print_infos(t_vm *vm);
void				print_champion_color(t_process *process, WINDOW *win);
void				del_ncurse(t_vm *vm);
int					and_op(t_vm *vm, t_process *p);
int					and_op2(t_vm *vm, t_process *p, int pc);
int					do_and(t_vm *vm, t_process *p, int v1, int v2);
int					set_reg_pos_and(t_vm *vm);
int					set_pc_bis(t_vm *vm, t_process *p);
void				ft_itobin(t_vm *vm, int nb);
int					find_special_pc(t_vm *vm);
int					find_special_pc_bis(t_vm *vm);
int					find_special_pc_terce(t_vm *vm);
int					find_special_pc_quarte(t_vm *vm);
int					launch_lld(t_vm *vm, t_process *process);
void				op_ld(int value, int *r, char *carry);
int					*fill_tab_sti(int reg);
void				option_v_four(t_vm *vm, int pc, t_process *p);
void				option_two(t_vm *vm, t_process *p, const int value1,
								const int value2);
void				kill_all_cursors(t_vm *vm);
int					wrong_params(t_vm *vm, t_process *p, int pc);
int					convert_4bytes(t_vm *vm, t_process *p, int index);
void				load_operations(t_vm *vm, int cycle);
int					get_cycle_to_wait(int op);
void				free_process(t_process *list);
void				free_player(t_vm *vm, int nb);
void				free_vm(t_vm *vm);
void				exit_error(char *message);
void				exit_code_size_error(t_vm *vm, int8_t error, int code_size,
										int player);
void				exit_args_error(int player);
void				update_ctd(t_vm *vm);
void				update_ctd_utils(t_vm *vm);

#endif
