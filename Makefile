OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

practica.tar:
	tar -cvf practica.tar Makefile *.hh *.cc

debug: program.exe
	gdb program.exe

program.exe: program.o Cluster.o Procesador.o Proceso.o ProcesosPendientes.o
	g++ -o program.exe program.o Cluster.o Procesador.o Proceso.o ProcesosPendientes.o $(OPCIONS)

program.o: program.cc Errores.hh
	g++ -c program.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh BinTree.hh Procesador.hh Errores.hh
	g++ -c Cluster.cc $(OPCIONS)

Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

ProcesosPendientes.o: ProcesosPendientes.cc ProcesosPendientes.hh Proceso.hh Cluster.hh
	g++ -c ProcesosPendientes.cc $(OPCIONS)

clean:
	rm *.o || rm program.exe || rm practica.tar
