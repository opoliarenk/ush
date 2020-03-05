NAME = ush

FILES = main \
	mx_wait_line \
	mx_connectors \
	mx_semicolon_check \
	mx_canon \
	mx_logic \
	mx_env_builtin \
	mx_builtin_export \
	mx_builtin_cd \
	mx_builtin_pwd \
	mx_builtin_echo \
	mx_hardsplit \
	mx_hardparser \
	mx_logical_or \
	mx_red_pipe \
	mx_sh_splite \
	mx_redirout \
	mx_redir \
	mx_newfor_bults \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uls.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic

LIB_A = libmx/libmx.a

all: install

install: ush

ush : $(SRC) $(INC)
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
