OUTPUT=main.out
MAIN=main.c
CONTACTS=contacts.c
UTILS= utils.c
SOURCE=src
BINARIES=bin

all:
	@make -s clean;
	@make -s build;
	@make -s run;

build:
	@mkdir $(BINARIES)
	@gcc -o $(BINARIES)/$(OUTPUT) $(SOURCE)/$(MAIN) $(SOURCE)/$(CONTACTS) $(SOURCE)/$(UTILS)
# @echo "project built"

clean:
	@rm -rf $(BINARIES)
#	@echo "binaries cleaned"

run:
	@chmod +x $(BINARIES)/$(OUTPUT)
	@./$(BINARIES)/$(OUTPUT)