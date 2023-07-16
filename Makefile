EXEC=solver

build: main.c
	gcc main.c -o ${EXEC}

clean:
	rm -f ./${EXEC}
	rm -f ./*.o