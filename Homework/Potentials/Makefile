# Authors: Santiago Talero & Laura Triana
# Subject: Computational Physics
# Title: Finites differences to Laplace equation

# The following rule compiles the file "laplace.cpp" and converts it in a    	binary named equals "laplace". All this way silent thanks to placing .SILENT at the beginning of the constructor.

.SILENT:

finites : laplace.cpp
	g++ laplace.cpp -o laplace

# La siguiente regla, compila y ejecuta el binario, por si no estaba
# compilado, si ya estaba compilado solo ejecuta el binario, luego lo 
# elimina ya que no es necesario y si se necesita el binario se ejecuta 
# la anterior acción. También crea una capeta para organizar los archivos de salida.

run : finites
	./laplace
	rm -rf output laplace plot.gp
	mkdir output
	mv -t ./output potential.png potentials.txt  2>/dev/null || true

clean :
	rm -rf output || true