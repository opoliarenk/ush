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
	mx_parser_4_cd \
	mx_part1_4_cd \
	mx_cd_back \
	mx_cd_s \
	mx_cd_P \
	mx_builtin_pwd \
	mx_parser_4_pwd \
	mx_builtin_echo \
	mx_parser_4_echo \
	mx_check_for_echoE \
	mx_echo_func_for_slesh \
	mx_del_4_echo \
	mx_check_double \
	mx_echo_part \
	mx_builtin_exit \
	mx_builtin_unset \
	mx_builtin_which \
	mx_look_in_path \
	mx_builtin_fg \
	mx_pid_pop_front \
	mx_parsing_4_fg \
	mx_check_list_4_fg \
	mx_printname_4_fg \
	mx_kill_4_fg \
	mx_is_built_in \
	mx_is_command \
	mx_is_slash \
	mx_strjoin_free \
	mx_hardsplit \
	mx_hardparser \
	mx_red_pipe \
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
	mx_doubl_red \
	mx_namedata \
	mx_pop_specific_4_pids \
	mx_logic_split \
	mx_move_cursor \
	mx_history \
	mx_checkout_char \
	mx_push_history \
	mx_if_P \
	mx_env_i \
	mx_mallocing_new \
	mx_env_u \
	mx_env_P \
	mx_env_not \
	mx_cmdand \
	mx_andor_input \
	mx_cmdor \
	mx_wspace \
	mx_clear_view \
	mx_not_a_char \
	mx_del \
	mx_if_notch \
	mx_signals \
	mx_var_rep_count \
	mx_var_rep_crt \
	mx_an_var \
	mx_hspl_count \
	mx_hspl_cr \
	mx_hspl_cr1 \
	mx_hash \
	mx_pre_substr \
	mx_sky_doubt \
	mx_sub_pars \
	mx_sub_doll_p \
	mx_doubl_d \
	mx_countingwh \
	mx_countingwh1 \
	mx_new_m_help \
	mx_new_m_sd \
	mx_new_s_d \
	mx_new_str_d \
	mx_sub_counts \
	mx_workb1 \
	mx_red_bh \
	mx_pipe_help \
	mx_fill_list \
	mx_fill_trig \
	mx_mainloop \
	mx_last_coms \
	mx_no_var_is \
	mx_env_var \
	mx_find_env \
	mx_env_exe \
	mx_env_unk \
	mx_usr_tilde \
	mx_user_prompt \
	mx_odd_slash \
	mx_good_repl_var \

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
