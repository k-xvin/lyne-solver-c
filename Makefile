EXEC=solve

build: main.c main.h
	gcc main.c -o ${EXEC}

clean:
	rm -f ./${EXEC}
	rm -f ./*.o