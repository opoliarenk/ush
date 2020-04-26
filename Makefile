NAME = ush

FILES = main \
	mx_wait_line \
	mx_connectors \
	mx_semicolon_check \
	mx_logic \
	mx_logical_or \
	mx_builtins \
	mx_builtin_env \
	mx_builtin_export \
	mx_builtin_cd \
	mx_builtin_pwd \
	mx_builtin_echo \
	mx_parser_4_echo \
	mx_check_for_echoE \
	mx_echo_func_for_slesh \
	mx_builtin_unset \
	mx_builtin_which \
	mx_is_built_in \
	mx_is_command \
	mx_is_slash \
	mx_strjoin_free \
	mx_hardsplit \
	mx_hardparser \
	mx_red_pipe \
	mx_sh_splite \
	mx_redirout \
	mx_redir \
	mx_newfor_bults \
	mx_delim_space \
	mx_strlen_for_2star \
	mx_canon_off \
	mx_input \
	mx_builtin_true \
	mx_builtin_false \
	mx_cut_spaces \
	mx_rederr \
	mx_redboth \
	mx_notbuiltin \
	mx_variable \
	mx_v_exist \
	mx_v_out \
	mx_unknown \
	mx_check_echo \
	mx_check_input \
	mx_sub \
	mx_replace \
	mx_end_sub \
	mx_countingw \
	mx_new_malloc \
	mx_pipe \
	mx_tilde \
	mx_mt \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uls.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic

LIB_A = libmx/libmx.a

all: install

install: $(NAME)

$(NAME) : $(SRC) $(INC)
	@make -C libmx install
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) $(OBJ) $(LIB_A) -o $(NAME)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@make -C libmx uninstall
	@rm -rf $(NAME)

clean:
	@make -C libmx clean
	@rm -rf obj

reinstall: uninstall install
