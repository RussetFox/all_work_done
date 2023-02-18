#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: Dron
	./Dron

Dron: obj obj/main.o obj/Dron_i_jego_czesci.o obj/Macierz.o obj/Wektor.o\
           obj/Dr3D_gnuplot_api.o obj/Elem_krajobrazu.o obj/Scena.o
	g++ -Wall -pedantic -std=c++0x -o Dron obj/main.o obj/Wektor.o\
                        obj/Macierz.o obj/Dron_i_jego_czesci.o obj/Elem_krajobrazu.o obj/Scena.o obj/Dr3D_gnuplot_api.o -lpthread

obj:
	mkdir obj

obj/Dr3D_gnuplot_api.o: inc/Dr3D_gnuplot_api.hh src/Dr3D_gnuplot_api.cpp 
	g++ -c ${CXXFLAGS} -o obj/Dr3D_gnuplot_api.o src/Dr3D_gnuplot_api.cpp

inc/Dr3D_gnuplot_api.hh: inc/Draw3D_api_interface.hh
	touch inc/Dr3D_gnuplot_api.hh

obj/main.o: src/main.cpp inc/Dron_i_jego_czesci.hh inc/Macierz.hh inc/Wektor.hh inc/Dr3D_gnuplot_api.hh inc/Elem_krajobrazu.hh inc/Scena.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/Dr3D_gnuplot_api.hh inc/Dron_i_jego_czesci.hh inc/Elem_krajobrazu.hh
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/Elem_krajobrazu.o: src/Elem_krajobrazu.cpp inc/Elem_krajobrazu.hh inc/Dr3D_gnuplot_api.hh inc/Dron_i_jego_czesci.hh
	g++ -c ${CXXFLAGS} -o obj/Elem_krajobrazu.o src/Elem_krajobrazu.cpp

obj/Dron_i_jego_czesci.o: src/Dron_i_jego_czesci.cpp inc/Dron_i_jego_czesci.hh inc/Dr3D_gnuplot_api.hh
	g++ -c ${CXXFLAGS} -o obj/Dron_i_jego_czesci.o src/Dron_i_jego_czesci.cpp

obj/Macierz.o: src/Macierz.cpp inc/Macierz.hh 
	g++ -c ${CXXFLAGS} -o obj/Macierz.o src/Macierz.cpp

obj/Wektor.o: src/Wektor.cpp inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor.o src/Wektor.cpp

clean:
	rm -f obj/*.o Dron