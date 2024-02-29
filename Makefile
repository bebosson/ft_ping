.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/
INC = ./inc/
INCH = ./inc/ft_ping.h
LIBFT = ./libft/libft.a
LIBFTH = ./libft/includes/
LIBDIR = ./libft/
BUILDIR = ./build/
BUILDOBJS = $(BUILDIR)main.o $(BUILDIR)debug.o $(BUILDIR)tool.o $(BUILDIR)code_icmp.o \
			$(BUILDIR)set_option.o $(BUILDIR)parse_option.o $(BUILDIR)send.o $(BUILDIR)addr.o
DEBUG =-g
all: ft_ping
ft_ping: $(BUILDIR)  $(LIBFT) $(BUILDOBJS) $(INCH)
	git submodule init
	git submodule update
	make -C ./libft/
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFTH) -o ft_ping $(BUILDOBJS) $(LIBFT)

$(BUILDIR):
	mkdir ./build/
$(LIBFT):
	make -C $(LIBDIR)

.SUFFIXES: .c .o

$(BUILDIR)%.o: $(SRC)%.c $(INCH) 
	$(CC) $(CCFLAGS) -I$(INC) -I$(LIBFTH) -c $< -o $@

clean:
	rm -rf $(BUILDIR)
	make -C $(LIBDIR) clean 
fclean:
	rm -rf ft_ping 
	make -C $(LIBDIR) fclean
	
debug: $(BUILDIR)  $(LIBFT) $(BUILDOBJS) $(INCH)
	make -C ./libft/
	$(CC) $(CFLAGS) $(DEBUG) -I$(INC) -I$(LIBFTH) -o ft_ping $(BUILDOBJS) $(LIBFT) 

re: fclean all
