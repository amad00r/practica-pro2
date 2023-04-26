#OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: build/program.o build/Cluster.o build/Procesador.o build/Proceso.o build/ProcesosPendientes.o
	g++ -o build/program.exe build/program.o build/Cluster.o build/Procesador.o build/Proceso.o build/ProcesosPendientes.o


build/program.o: src/program.cc src/Errores.hh
	g++ -c src/program.cc $(OPCIONS)
	mv program.o build/program.o

build/Cluster.o: src/Cluster.cc src/Cluster.hh src/BinTree.hh src/Procesador.hh src/Errores.hh
	g++ -c src/Cluster.cc $(OPCIONS)
	mv Cluster.o build/Cluster.o

build/Procesador.o: src/Procesador.cc src/Procesador.hh src/Proceso.hh
	g++ -c src/Procesador.cc $(OPCIONS)
	mv Procesador.o build/Procesador.o

build/Proceso.o: src/Proceso.cc src/Proceso.hh
	g++ -c src/Proceso.cc $(OPCIONS)
	mv Proceso.o build/Proceso.o

build/ProcesosPendientes.o: src/ProcesosPendientes.cc src/ProcesosPendientes.hh src/Proceso.hh src/Cluster.hh
	g++ -c src/ProcesosPendientes.cc $(OPCIONS)
	mv ProcesosPendientes.o build/ProcesosPendientes.o

clean:
	rm build/*.o
	rm build/program.exe
