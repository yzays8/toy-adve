SRCDIR = src
FILE_PATH = $(abspath $(if $(filter /%,$(FILE)),$(FILE),$(dir $(lastword $(MAKEFILE_LIST)))$(FILE)))

.PHONY: all clean run test
all:
	make all -C $(SRCDIR)

clean:
	make clean -C $(SRCDIR)

run:
	make run FILE=$(FILE_PATH) -C $(SRCDIR)

test:
	make test -C $(SRCDIR)
