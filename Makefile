NAME = uls

SRCD = src
INCD = inc
OBJD = obj
LBMXD = libmx

LMBX = libmx.a
INC = uls.h
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

INCLUDE = -I $(LBMXD) \
	-I $(INCD) \

LBMXS = $(addprefix $(LBMXD)/, $(LMBX))
INCS = $(addprefix $(INCD)/, $(INC))
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))
	
CFLAGS = -std=c99 $(addprefix -W, all extra error pedantic)

all: install clean

install: $(LBMXS) $(NAME)

$(LBMXS):
	@make -sC $(LBMXD) install

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LBMXS) $(OBJS) -o $@

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

uninstall: clean
	@make -sC $(LBMXD) $@
	@rm -rf $(NAME)	

clean:
	@make -sC $(LBMXD) $@
	@rm -rf $(OBJD)

reinstall: clean all
