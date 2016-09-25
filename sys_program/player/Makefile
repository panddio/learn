DIR_INC := ./src/inc
DIR_SRC := ./src
DIR_OBJ := ./obj
DIR_BIN := ./bin

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = mplayer

#BIN_TARGET = ${DIR_BIN}/${TARGET} # 目标存放在 bin目录
BIN_TARGET = ./${TARGET}  # 目标存放在当前目录

CC = gcc
INCFAG = -I$(DIR_INC)
CFLAGES = -lpthread `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs libglade-2.0`

$(BIN_TARGET):$(OBJ)
	$(CC) $(OBJ)  -o $@ $(CFLAGES)
    
$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(INCFAG) -c  $< -o $@ $(CFLAGES)
	
.PHONY:clean
clean:
#	find $(DIR_OBJ) -name *.o -exec rm -rf {}\ ;
	rm ${DIR_OBJ}/* ${TARGET}