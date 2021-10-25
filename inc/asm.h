/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:18:49 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/12 18:25:17 by ekelkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define WRONG_EXTENSION		"ERROR: wrong file extension"
# define FILE_NAME_TOO_LONG		"ERROR: file name too long"
# define ERROR_OPEN_FILE		"ERROR: cannot open file"
# define ERROR_READ_FILE		"ERROR: cannot read file"
# define ERROR_CREATE_FILE		"ERROR: cannot create file"
# define ERROR_MALLOC			"ERROR: malloc failed"

/*
** Token types
*/

typedef enum
{
	COMMAND, STRING, LABEL, INSTRUCTION, REGISTER, DIRECT, DIRECT_LABEL,
	INDIRECT, INDIRECT_LABEL, SEPARATOR, ENDLINE, END
}	t_type;

static char		*g_type[] = {
	"COMMAND", "STRING", "LABEL", "INSTRUCTION", "REGISTER", "DIRECT",
	"DIRECT_LABEL", "INDIRECT", "INDIRECT_LABEL", "SEPARATOR",
	"ENDLINE", "END"
};

static char		*g_type2[] = {
	"command", "string", "label", "instruction", "register", "direct",
	"direct_label", "indirect", "indirect_label", "separator",
	"endline", "end"
};

typedef struct	s_token
{
	size_t				line;
	size_t				column;
	char				*content;
	t_type				type;
	char				pad[4];
	struct s_token		*next;
}				t_token;

typedef struct	s_mention
{
	size_t				line;
	size_t				column;
	size_t				pos;
	size_t				op_pos;
	size_t				size;
	t_type				token_type;
	char				pad[4];
	char				*token_content;
	struct s_mention	*next;
}				t_mention;

typedef struct	s_label
{
	char				*name;
	ssize_t				op_pos;
	t_mention			*mentions;
	struct s_label		*next;
}				t_label;

typedef struct	s_parsing
{
	size_t				pos;
	size_t				op_pos;
	size_t				code_size;
	size_t				output_length;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				pad[6];
	char				*code;
}				t_parsing;

typedef struct	s_lexing
{
	int					fd;
	char				pad[4];
	size_t				line;
	size_t				column;
	t_token				*tokens;
	t_label				*labels;
}				t_lexing;

void			lex_source_code(t_lexing *s);
char			*lex_line(t_lexing *s, char *line);
t_token			*create_token(t_lexing *s, t_type type);
void			add_token(t_token **list, t_token *new);
int8_t			is_delimiter(char c);
int8_t			is_register(char *arg);
int8_t			is_header_lexing_finished(t_lexing *s);
void			parse_source_code(t_lexing *s, t_parsing *p);
void			parse_header(t_parsing *p, t_token **curr);
t_token			*parse_inst(t_lexing *s, t_parsing *p, t_token *curr, t_op *op);
long long		num(char *str);
int8_t			get_arg_type(t_type type);
t_label			*create_label(char *name, ssize_t op_pos);
void			add_label(t_label **l, t_label *new);
t_mention		*create_mention(t_parsing *p, t_token *t, size_t size);
void			add_ment(t_lexing *s, t_parsing *p, t_token *curr, int8_t size);
t_label			*find_label(t_label *l, char *name);
void			write_bytecode_file(char *filename, t_parsing *p);
void			int2byte(char *s, size_t pos, int32_t value, size_t size);
void			free_s(t_lexing *s, t_parsing *p);

void			exit_error(char *message);
void			exit_lexical_error(t_lexing *s, char *line);
void			exit_token_error(t_token *t);
void			exit_header_error(char *cmd);
void			exit_label_error(t_label *l);
void			exit_instruction_error(t_token *t);
void			exit_arg_type_error(t_op *op, int arg_num, t_token *t);

#endif
