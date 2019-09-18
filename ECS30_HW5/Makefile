all: binary_matrix_driver coordinate_driver conways_game_of_life_driver list_driver

clean:
	rm *.o
	rm *_driver

binary_matrix_driver: binary_matrix.o binary_matrix_driver.o
	gcc binary_matrix.o binary_matrix_driver.o -o binary_matrix_driver

coordinate_driver: coordinate.o coordinate_driver.o
	gcc coordinate.o coordinate_driver.o -o coordinate_driver -lm

conways_game_of_life_driver: conways_game_of_life.o coordinate.o binary_matrix.o list.o conways_game_of_life_driver.o
	gcc conways_game_of_life.o coordinate.o binary_matrix.o list.o conways_game_of_life_driver.o -o conways_game_of_life_driver

list_driver: list.o coordinate.o list_driver.o
	gcc list.o coordinate.o list_driver.o -o list_driver

binary_matrix.o: binary_matrix.c
	gcc -g -c binary_matrix.c

coordinate.o: coordinate.c
	gcc -g -c coordinate.c

conways_game_of_life.o: conways_game_of_life.c
	gcc -g -c conways_game_of_life.c

list.o: list.c
	gcc -g -c list.c
