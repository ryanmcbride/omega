CXX		  := g++
CXX_FLAGS := -w -g -DBSD -std=c++11 -L/usr/local/opt/ncurses/lib -I/usr/local/opt/ncurses/include
CC        := gcc
C_FLAGS   := -w -g -DBSD -I/usr/local/opt/ncurses/include

BIN		:= bin
SRC		:= src
GEN_CLR_SRC		:= genclrsrc
TEST_CURSE_SRC		:= curses
TOOLS_SRC := tools
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lncurses
EXECUTABLE	:= omega
GEN_CLR_EXECUTABLE	:= genclr
TEST_CURSE_EXECUTABLE	:= testcurse
DECRYPT_EXECUTABLE := decrypt
ENCRYPT_EXECUTABLE := encrypt

OMEGAC	:=	omegac.a


all: $(BIN)/$(GEN_CLR_EXECUTABLE) $(BIN)/$(DECRYPT_EXECUTABLE) $(BIN)/$(ENCRYPT_EXECUTABLE) $(BIN)/$(EXECUTABLE) $(BIN)/$(TEST_CURSE_EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(GEN_CLR_EXECUTABLE)
	./$(BIN)/$(DECRYPT_EXECUTABLE)
	./$(BIN)/$(ENCRYPT_EXECUTABLE)
	./$(BIN)/$(TEST_CURSE_EXECUTABLE)

$(BIN)/$(OMEGAC): $(SRC)/*.c
	$(CC) $(C_FLAGS) -c -I$(INCLUDE) $^
	mv *.o $(SRC)
	ar rvs $(BIN)/$(OMEGAC) $(^:.c=.o)
	rm -rf $(SRC)/*.o

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)
	./encryptall.sh
	cp -rf omegalib $(BIN)/omegalib

$(BIN)/$(GEN_CLR_EXECUTABLE): $(GEN_CLR_SRC)/*.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(DECRYPT_EXECUTABLE): $(TOOLS_SRC)/decrypt.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(ENCRYPT_EXECUTABLE): $(TOOLS_SRC)/crypt.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(TEST_CURSE_EXECUTABLE): $(TEST_CURSE_SRC)/cursetest.c
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/omegalib
	-rm -rf $(BIN)/omega*
	-rm -rf $(BIN)/encrypt*
	-rm -rf $(BIN)/decrypt*
	-rm -rf $(BIN)/genclr*
	-rm -rf $(BIN)/testcurse*
	-rm -rf *.o