NAME = uls

NLIB = libmx/libmx.a

HDR = uls.h

SRC = main.c \
	mx_new_app.c \
	mx_read_args.c \
	mx_make_command.c \
	mx_default_commands.c \
	mx_print_args_error.c \
	mx_print_args_file.c \
	mx_print_args_directories.c \
	mx_print_one_directory.c \
	mx_new_lfa.c \
	mx_produce_list_attr.c \
	mx_make_attr_struct.c \
	mx_attr_struct_res.c \
	mx_apply.c \
	mx_apply_filters.c \
	mx_apply_sort.c \
	mx_comparators.c \
	mx_comparators_r.c \
	mx_apply_printmode.c \
	mx_apply_format_time.c \
	mx_print_lines.c \
	mx_clear_flags.c \
	mx_filter_flags.c \
	mx_printable_lines.c \
	mx_read_flags.c \
	mx_std_and_pipe.c \
	mx_print_std_names.c \
	mx_std_lists.c \
	mx_view_with_comas.c \
	mx_filter_out_col.c \
	mx_free.c \
	mx_error_flag.c \
	mx_apply_header.c \
	mx_format_size.c \
	mx_error_message.c \
	mx_byte_format.c \
	mx_major_minor.c \
	mx_output_flags.c \

OBJ = $(SRC:.c=.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	@cd libmx && make -f Makefile all
	@cp $(addprefix src/, $(SRC)) $(addprefix inc/, $(HDR)) libmx/inc/libmx.h .
	@clang $(CFLAG) -c $(SRC) -I $(HDR) 
	@mkdir -p obj
	@clang $(CFLAG) $(OBJ) $(NLIB) -o $(NAME)
	@mv $(OBJ) ./obj
	@rm -rf $(SRC) $(HDR) libmx.h

uninstall: clean
	@cd libmx && make -f Makefile uninstall
	@rm -rf $(NAME)

clean:
	@cd libmx && make -f Makefile clean
	@rm -rf $(OBJ) ./obj

reinstall: uninstall install
