SRCDIR = src

.PHONY: all clean run
all:
	make all -C $(SRCDIR)

clean:
	make clean -C $(SRCDIR)

run:
	make run -C $(SRCDIR)
