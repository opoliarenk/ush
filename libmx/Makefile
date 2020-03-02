NAME = libmx.a

FILES = mx_printchar \
		mx_realloc \
		mx_file_to_str \
		mx_print_unicode \
		mx_printstr \
		mx_print_strarr \
		mx_printint \
		mx_pow \
		mx_sqrt \
		mx_hex_to_nbr \
		mx_nbr_to_hex \
		mx_itoa \
		mx_foreach \
		mx_binary_search \
		mx_bubble_sort \
		mx_strlen \
		mx_swap_char \
		mx_str_reverse \
		mx_strdel \
		mx_del_strarr \
		mx_get_char_index \
		mx_strdup \
		mx_strndup \
		mx_strcpy \
		mx_strncpy \
		mx_strcmp \
		mx_strncmp \
		mx_strcat \
		mx_strstr \
		mx_get_substr_index \
		mx_count_substr \
		mx_count_words \
		mx_strnew \
		mx_strtrim \
		mx_del_extra_spaces \
		mx_strsplit \
		mx_strjoin \
		mx_replace_substr \
		mx_memset \
		mx_memcpy \
		mx_memccpy \
		mx_memcmp \
		mx_memchr \
		mx_memrchr \
		mx_memmem \
		mx_memmove \
		mx_realloc \
		mx_create_node \
		mx_push_front \
		mx_push_back \
		mx_pop_front \
		mx_pop_back \
		mx_strlen \
		mx_list_size \
		mx_ultra_strtrim \
		mx_ultra_del_extra_spaces \
		mx_skip_substr_index \
		mx_strncmp \
		mx_is_space \
		mx_strjoin \
		mx_printerr \
		mx_del_intarr \
		mx_atoi \
		mx_is_alpha \
		mx_isdigit \
		mx_sort_list \
		mx_arrlen \

SRC_PREFFIX = $(addprefix src/, $(FILES))

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

LIB = inc/libmx.h

all: install

install: libmx

libmx: $(SRC) $(INC)
	@clang $(CFLAGS) -c $(SRC)
	@ar -rc $(NAME) $(OBJ)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf obj

reinstall: uninstall install
