all: memory-user null leak tlb

memory-user: memory-user.c
	gcc -o memory-user memory-user.c

null: null.c
	gcc -g -o null null.c

leak: leak.c
	gcc -g -o leak leak.c

tlb: tlb.c
	gcc -o tlb tlb.c

clean:
	rm -f memory-user null leak tlb
	rm -f *.txt

