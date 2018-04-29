HEADERS = Mitnic.h Ciphers.h UserInput.h

C_SRCS  = Driver.c Mitnick.c UserInput.c
C_OBJS  = Driver.o Mitnick.o UserInput.o
EXEC    = Decipher

# -c: compiles or assembles source files, but does not link. Result object files
# -std=c99: specifies the version of c being compiled (published in 1999)
GCC       = gcc
GCC_FLAGS = -c -std=c99

RM = rm

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Standard rules
.c.o:
	@echo "Compiling C source files seperately to obeject files..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

$(EXEC): $(C_OBJS) 
	@echo "Linking all object modules..."
	$(GCC) -o $(EXEC) $(C_OBJS)
	@echo ""
	@echo "${GREEN}Successful compilation.${NC}"
	
clean:
	@echo "Cleaning Deciphering_Tool directory..."
	$(RM) *.o $(EXEC)
	@echo "\nClean."
