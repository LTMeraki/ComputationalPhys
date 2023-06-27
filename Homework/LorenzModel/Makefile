# Autores: Laura Triana y Sebastian Manrique
# Curso: Física Computacional
# Título: Modelo de Lorenz RK4

# La siguiente regla compila el archivo "lorenzcode.cpp" y lo convierte 
# en un binario llamado de igual "lorenz". Todo esto de manera 
# silenciosa gracias a colocar .SILENT al inicio del constructor.

.SILENT:

lorenz : lorenzcode.cpp
	g++ lorenzcode.cpp -o lorenz

# La siguiente regla, compila y ejecuta el binario, por si no estaba
# compilado, si ya estaba compilado solo ejecuta el binario, luego lo 
# elimina ya que no es necesario y si se necesita el binario se ejecuta 
# la anterior acción. También crea una capeta para organizar los archivos de salida.

run : lorenz 
	./lorenz
	rm -rf lorenzfolder lorenz
	mkdir lorenzfolder
	mv -t ./lorenzfolder lorenz.dat time.png fase.png 3d.png 2>/dev/null || true

.PHONY : plot
plot :
	cd lorenzfolder && gnuplot -e " \
	set terminal pngcairo enhanced size 800,600 font 'Latin Modern Roman,12'; \
	set output 'time.png'; \
	set multiplot layout 3,1; \
	set title 'Gráfica temporal de {/:italic x}'; \
	set size 1, 0.5; \
	set origin 0, 0.5; \
	plot 'lorenz.dat' using 1:2 with lines notitle; \
	set title 'Gráfica temporal de {/:italic y}'; \
	set size 0.5, 0.5; \
	set origin 0, 0; \
	plot 'lorenz.dat' using 1:3 with lines notitle; \
	set title 'Gráfica temporal de {/:italic z}'; \
	set size 0.5, 0.5; \
	set origin 0.5, 0; \
	plot 'lorenz.dat' using 1:4 with lines notitle; \
	unset multiplot; \
	set output 'fase.png'; \
	set multiplot layout 3,1; \
	set title 'Espacio de fase {/:italic x} vs  {/:italic z} '; \
	set size 1, 0.5; \
	set origin 0, 0.5; \
	plot 'lorenz.dat' using 2:4 with lines notitle; \
	set title 'Espacio de fase {/:italic x} vs  {/:italic y}'; \
	set size 0.5, 0.5; \
	set origin 0, 0; \
	plot 'lorenz.dat' using 2:3 with lines notitle; \
	set title 'Espacio de fase {/:italic y} vs  {/:italic z}'; \
	set size 0.5, 0.5; \
	set origin 0.5, 0; \
	plot 'lorenz.dat' using 3:4 with lines notitle; \
	unset multiplot; \
	set output '3d.png'; \
	set xlabel 'Estado {/:italic x}'; \
	set ylabel 'Estado {/:italic y}'; \
	set zlabel 'Estado {/:italic z}'; \
	set title 'Espacio de fase {/:italic x} vs  {/:italic y} vs  {/:italic z} '; \
	splot 'lorenz.dat' using 2:3:4 with lines notitle"

# Finalmente, esta regla elimina el binario, los archivos .txt y .gp 
# junto a las gráficas para volver a ejecutar y tener todo limpio, en el 
# caso en el que el archivo exista, la función "-f" lo ignora, así no 
# genera ningún tipo de conflicto.

.PHONY : clean
clean :
	rm -f lorenz lorenz.dat time.png fase.png 3d.png || true
	rm -rf lorenzfolder/