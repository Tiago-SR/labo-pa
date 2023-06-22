INTERFACES = ICollection/interfaces/
COLECCIONES = ICollection/collections/
CLASES = src/clases
DATATYPES = src/datatype
OBJETOS = dtAsignatura.o dtDireccion.o dtEmpresa.o  dtEstudiante.o dtEstudianteTodo.o dtFecha.o dtOfertaLaboral.o dtRangoSalario.o dtSeccion.o dtSucursal.o Asignatura.o Empresa.o Anotarse.o Estudiante.o Factory.o ISistema.o Seccion.o OfertaLaboral.o  Sistema.o Sucursal.o Integer.o String.o List.o ICollection.o ICollectible.o IIterator.o IKey.o OrderedKey.o OrderedDictionaryEntry.o ListNode.o ListIterator.o IDictionary.o OrderedDictionary.o main.o


run:
	clear
	make clean
	make all
	make clean
	clear
	./programa

all: $(OBJETOS)
	g++ $(OBJETOS) -o programa

dtAsignatura.o: ICollectible.o
	g++ -c $(DATATYPES)/dtAsignatura.cpp

dtDireccion.o:
	g++ -c $(DATATYPES)/dtDireccion.cpp

dtEmpresa.o: ICollectible.o
	g++ -c $(DATATYPES)/dtEmpresa.cpp

dtEstudiante.o: ICollectible.o
	g++ -c $(DATATYPES)/dtEstudiante.cpp

dtEstudianteTodo.o: dtFecha.o
	g++ -c $(DATATYPES)/dtEstudianteTodo.cpp

dtFecha.o: 
	g++ -c $(DATATYPES)/dtFecha.cpp

dtOfertaLaboral.o: dtRangoSalario.o dtFecha.o ICollectible.o
	g++ -c $(DATATYPES)/dtOfertaLaboral.cpp

dtRangoSalario.o: 
	g++ -c $(DATATYPES)/dtRangoSalario.cpp

dtSeccion.o: ICollectible.o
	g++ -c $(DATATYPES)/dtSeccion.cpp

dtSucursal.o: ICollectible.o dtDireccion.o
	g++ -c $(DATATYPES)/dtSucursal.cpp

Asignatura.o: ICollectible.o dtAsignatura.o
	g++ -c $(CLASES)/Asignatura.cpp

Empresa.o: ICollectible.o IDictionary.o ICollection.o OrderedDictionary.o List.o String.o dtEmpresa.o dtDireccion.o Sucursal.o OfertaLaboral.o
	g++ -c $(CLASES)/Empresa.cpp

Estudiante.o: ICollectible.o IDictionary.o ICollection.o OrderedDictionary.o List.o Integer.o dtDireccion.o dtFecha.o dtEstudiante.o dtEstudianteTodo.o Asignatura.o Anotarse.o
	g++ -c $(CLASES)/Estudiante.cpp
	
Anotarse.o: 
	g++ -c $(CLASES)/Anotarse.cpp


Factory.o: ISistema.o Sistema.o
	g++ -c $(CLASES)/Factory.cpp

ISistema.o:
	g++ -c $(CLASES)/ISistema.cpp

OfertaLaboral.o: ICollection.o IDictionary.o ICollectible.o OrderedDictionary.o List.o Integer.o dtRangoSalario.o dtFecha.o dtOfertaLaboral.o dtSeccion.o dtSucursal.o dtEmpresa.o Asignatura.o Seccion.o Anotarse.o
	g++ -c $(CLASES)/OfertaLaboral.cpp

Seccion.o: ICollectible.o ICollection.o IDictionary.o Integer.o OrderedDictionary.o List.o dtSeccion.o dtSucursal.o dtEmpresa.o
	g++ -c $(CLASES)/Seccion.cpp

Sistema.o: dtFecha.o dtDireccion.o dtOfertaLaboral.o dtEstudianteTodo.o dtSeccion.o dtSucursal.o dtEmpresa.o dtRangoSalario.o IDictionary.o ICollection.o OrderedDictionary.o List.o String.o Integer.o Empresa.o Sucursal.o Seccion.o Asignatura.o OfertaLaboral.o Estudiante.o
	g++ -c $(CLASES)/Sistema.cpp

Sucursal.o: Seccion.o OfertaLaboral.o ICollectible.o ICollection.o IDictionary.o OrderedDictionary.o List.o String.o dtDireccion.o dtSucursal.o dtEmpresa.o
	g++ -c $(CLASES)/Sucursal.cpp


Integer.o: ICollection/Integer.h ICollectible.o OrderedKey.o
	g++ -c ICollection/Integer.cpp

String.o: ICollection/String.h ICollectible.o OrderedKey.o
	g++ -c ICollection/String.cpp

List.o: ICollection.o ListIterator.o $(COLECCIONES)List.h
	g++ -c $(COLECCIONES)List.cpp

ICollection.o: IIterator.o ICollectible.o $(INTERFACES)ICollection.h
	g++ -c $(INTERFACES)ICollection.cpp

ICollectible.o: $(INTERFACES)ICollectible.h
	g++ -c $(INTERFACES)ICollectible.cpp 

IIterator.o: $(INTERFACES)IIterator.h $(INTERFACES)ICollectible.o
	g++ -c $(INTERFACES)IIterator.cpp 

IKey.o: $(INTERFACES)IKey.h
	g++ -c $(INTERFACES)IKey.cpp

OrderedKey.o: $(INTERFACES)OrderedKey.h $(INTERFACES)IKey.o 
	g++ -c $(INTERFACES)OrderedKey.cpp

OrderedDictionaryEntry.o: $(COLECCIONES)OrderedDictionaryEntry.h ICollectible.o OrderedKey.o
	g++ -c $(COLECCIONES)OrderedDictionaryEntry.cpp

ListNode.o: $(COLECCIONES)ListNode.h ICollectible.o
	g++ -c $(COLECCIONES)ListNode.cpp

ListIterator.o: $(COLECCIONES)ListIterator.h ListNode.o 
	g++ -c $(COLECCIONES)ListIterator.cpp

IDictionary.o: $(INTERFACES)IDictionary.h IIterator.o ICollectible.o IKey.o
	g++ -c $(INTERFACES)IDictionary.cpp

OrderedDictionary.o: $(COLECCIONES)OrderedDictionary.h IDictionary.o OrderedDictionaryEntry.o ListIterator.o
	g++ -c $(COLECCIONES)OrderedDictionary.cpp

main.o:
	g++ -c main.cpp

clean:
	rm -f *.o $(INTERFACES)*.o $(COLECCIONES)*.o

