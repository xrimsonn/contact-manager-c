OUTPUT=main.out
MAIN=main.c
CONTACTS=contacts.c
SOURCE=src
BINARIES=bin

all:
	@make -s clean;
	@make -s build;
	@make -s run;
	@make -s clean;

build:
	@mkdir $(BINARIES)
	@gcc -o $(BINARIES)/$(OUTPUT) $(SOURCE)/$(MAIN) $(SOURCE)/$(CONTACTS)
# @echo "project built"

clean:
	@rm -rf $(BINARIES)
#	@echo "binaries cleaned"

run:
	@chmod +x $(BINARIES)/$(OUTPUT)
	@./$(BINARIES)/$(OUTPUT)