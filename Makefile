CXX		  := g++
CXX_FLAGS := -w -g -DBSD -std=c++11
CC        := gcc
C_FLAGS   := -Wall -Wextra -g -DBSD

BIN		:= bin
SRC		:= src
GEN_CLR_SRC		:= genclrsrc
TOOLS_SRC := tools
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lncurses
EXECUTABLE	:= omega
GEN_CLR_EXECUTABLE	:= genclr
DECRYPT_EXECUTABLE := decrypt
ENCRYPT_EXECUTABLE := encrypt

OMEGAC	:=	omegac.a


all: $(BIN)/$(GEN_CLR_EXECUTABLE) $(BIN)/$(DECRYPT_EXECUTABLE) $(BIN)/$(ENCRYPT_EXECUTABLE) $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(GEN_CLR_EXECUTABLE)
	./$(BIN)/$(DECRYPT_EXECUTABLE)
	./$(BIN)/$(ENCRYPT_EXECUTABLE)

$(BIN)/$(OMEGAC): $(SRC)/*.c
	$(CC) $(C_FLAGS) -c -I$(INCLUDE) $^
	mv *.o $(SRC)
	ar rvs $(BIN)/$(OMEGAC) $(^:.c=.o)
	rm -rf $(SRC)/*.o

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(BIN)/$(OMEGAC)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(BIN)/$(OMEGAC) $^ -o $@ $(LIBRARIES)
	./encryptall.sh
	cp -rf omegalib $(BIN)/omegalib

$(BIN)/$(GEN_CLR_EXECUTABLE): $(GEN_CLR_SRC)/*.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(DECRYPT_EXECUTABLE): $(TOOLS_SRC)/decrypt.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(ENCRYPT_EXECUTABLE): $(TOOLS_SRC)/crypt.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/omegalib
	-rm -rf $(BIN)/omega*
	-rm -rf $(BIN)/encrypt*
	-rm -rf $(BIN)/decrypt*
	-rm -rf $(BIN)/genclr*