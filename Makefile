CXX		  := gcc
CXX_FLAGS := -Wall -Wextra -g -DBSD

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


all: $(BIN)/$(GEN_CLR_EXECUTABLE) $(BIN)/$(DECRYPT_EXECUTABLE) $(BIN)/$(ENCRYPT_EXECUTABLE) $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(GEN_CLR_EXECUTABLE)
	./$(BIN)/$(DECRYPT_EXECUTABLE)
	./$(BIN)/$(ENCRYPT_EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c*
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
	./encryptall.sh
	cp -rf omegalib $(BIN)/omegalib

$(BIN)/$(GEN_CLR_EXECUTABLE): $(GEN_CLR_SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(DECRYPT_EXECUTABLE): $(TOOLS_SRC)/decrypt.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(ENCRYPT_EXECUTABLE): $(TOOLS_SRC)/crypt.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/omegalib
	-rm -rf $(BIN)/omega*
	-rm -rf $(BIN)/encrypt*
	-rm -rf $(BIN)/decrypt*
	-rm -rf $(BIN)/genclr*