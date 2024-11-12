NAME		:=	client

SERVER		:=	server

CLIENTB		:=	client_bonus

SERVERB		:=	server_bonus

LIB			:= libftprintf.a

DIR_CLIENT	:=	srcs/client/

DIR_SERVER	:=	srcs/server/

SRC_CLIENT	:=	client.c

SRC_SERVER	:=	server.c

SRC_CLIENTB	:=	client_bonus.c

SRC_SERVERB	:=	server_bonus.c

OBJ_CLIENT	:=	$(patsubst %.c, $(DIR_CLIENT)%.o, $(SRC_CLIENT))

OBJ_SERVER	:=	$(patsubst %.c, $(DIR_SERVER)%.o, $(SRC_SERVER))

OBJ_CLIENTB	:=	$(patsubst %.c, $(DIR_CLIENT)%.o, $(SRC_CLIENTB))

OBJ_SERVERB	:=	$(patsubst %.c, $(DIR_SERVER)%.o, $(SRC_SERVERB))

CC = 	cc

FLAGS =	-Wall -Wextra -Werror

all : $(NAME) $(SERVER)

$(NAME) : $(OBJ_CLIENT) $(LIB)
	$(CC) -o $(NAME) $(OBJ_CLIENT) $(LIB)

$(SERVER) :  $(OBJ_SERVER) $(LIB)
	$(CC) -o $(SERVER) $(OBJ_SERVER) $(LIB)

$(LIB):
	make -C srcs/printf
	mv srcs/printf/libftprintf.a ./
	
#--------------------BONUS PART---------------------

bonus: $(CLIENTB) $(SERVERB)

$(CLIENTB): $(OBJ_CLIENTB) $(LIB)
	$(CC) -o $(CLIENTB) $(OBJ_CLIENTB) $(LIB)

$(SERVERB): $(OBJ_SERVERB) $(LIB)
	$(CC) -o $(SERVERB) $(OBJ_SERVERB) $(LIB)

#---------------------------------------------------

$(DIR_CLIENT)%.o: $(DIR_CLIENT)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_SERVER)%.o: $(DIR_SERVER)%.c
	$(CC) $(FLAGS) -c $< -o $@
	
clean : 
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -f $(OBJ_CLIENTB) $(OBJ_SERVERB)
	make -C srcs/printf clean

fclean : clean
	rm -f $(NAME) $(SERVER)
	rm -f $(CLIENTB) $(SERVERB)
	rm -f $(LIB)

re : fclean all

PHONY : re clean fclean all bonus
