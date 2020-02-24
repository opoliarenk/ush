NAME = ush

DIROBJ = obj

FILES = main \
	mx_read_line \
	mx_strsplit \

SRC = $(addprefix src/, $(addsuffix .c,$(FILES)))

OUT = $(addsuffix .o, $(FILES))

INC = inc/ush.h

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: uninstall install
install:
	@mkdir $(DIROBJ)
	@clang $(FLAGS) $(SRC) -c $(SRC) -I $(INC)
	@mv $(OUT) $(DIROBJ)
	@clang $(FLAGS) $(SRC) -o $(NAME) -I $(INC)

uninstall: clean
	@rm -rf $(NAME)
clean: 	
	@rm -rf $(DIROBJ)
reinstall: uninstall install 