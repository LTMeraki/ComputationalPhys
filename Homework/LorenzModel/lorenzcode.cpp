// Autores: Laura Triana y Sebastian Manrique
// Curso: Física Computacional
// Título: Modelo de Lorenz RK4

// Declaración de las librerías necesarias para la ejecución

#include <iostream> // Permite imprimir y solicitar datos en terminal
#include <fstream> // Permite manipular documentos externos
#include <cmath> // Librería matemática
#include <iomanip> // Usada para el comando "setprecision()"

/*
Declaración de la clase Lorenz:
    Esta clase es la clase principal de todo el código la cual me generará un objeto con ciertos atributos asociados a la solución del modelo de Lorenz, tales como las condiciones iniciales y los parámetros libres. De la misma manera posee un método para solucionar numéricamente el modelo mediante el método de Runge-Kutta de cuarto orden.

    Dentro del fragmento público se pueden encontrar los atributos dados por el usuario (los mencionados previamente) junto al método de ejecución. Finalmente, dentro del fragmento privado se encuentran el resto de atributos asociados al objeto tales como los parámetros libres pero ahora con la propiedad constante, los valores de las funciones x, y y z junto a los métodos asociados a las ecuaciones diferenciales que caracterizan el sistema.
*/

class Lorenz {
public:
    Lorenz(double x0, double y0, double z0, double s, double r, double b);
    void run(double h, double t);
private:
    const double s, r, b;
    double x, y, z;
    double dxdt(double x, double y, double z);
    double dydt(double x, double y, double z);
    double dzdt(double x, double y, double z);
};

// Constructor de la clase Lorenz

Lorenz::Lorenz(double x0, double y0, double z0, double s, double r, double b) :
    x(x0), y(y0), z(z0), s(s), r(r), b(b) {} // Lista de inicialización

/*
Declaración del método de ejecución de la clase Lorenz:
    El método "run", como ya se mencionó previamente, se encarga de solucionar el modelo de Lorenz a través del método numérico Runge-Kutta de cuarto orden.

    (1) Este apartado se encarga de abrir el archivo "lorenz.dat".
    (2) Inicia los vectores "k" para aplicar el método RK4.
    (3) Envía las condiciones iniciales al archivo "lorenz.dat".
    (4) Ciclo "for" que permite realizar las respectivas iteraciones del método RK4 basado en el tiempo de evolución que se indique. A su vez, guarda los valores obtenidos tras iteración directamente en el archivo "lorenz.dat".
    (5) Ciclo "for" que calcula las diferentes k's asociadas al método RK4.
    (6) Uso de ternarios como condiciones para la ejecución del ciclo.
    (7) Con base en las condiciones de los ternarios y conforme va avanzando el ciclo, se guardan los valores de cada k en un array correspondiente, siendo que k1,k2,k3,k4 para i = 0,1,2,3.
    (8) Cálculo del siguiente valor iterativo dado por el ciclo "for" principal.
    (9) Envío de datos al archivo "lorenz.dat".
    (10) Cierra el archivo "lorenz.dat".
*/

void Lorenz::run(double h, double t) {
    std::ofstream outfile("lorenz.dat", std::ios::trunc); // (1)

    double kx[4], ky[4], kz[4]; // (2)

    outfile << "0" << "\t" << std::setprecision(10) << x << "\t" << std::setprecision(10) << y << "\t" << std::setprecision(10) << z << std::endl; // (3)

    for (double dt = 0; dt <= t; dt += h) { // (4)

        for(int i = 0; i < 4; i++) { // (5)
        // (6)
            double kx_ = x + ((i == 0) ? 0 : (i == 3) ? h*kx[i-1] : (h/2)*kx[i-1]);
            double ky_ = y + ((i == 0) ? 0 : (i == 3) ? h*ky[i-1] : (h/2)*ky[i-1]);
            double kz_ = z + ((i == 0) ? 0 : (i == 3) ? h*kz[i-1] : (h/2)*kz[i-1]);
        // (7)
            kx[i] = dxdt(kx_, ky_, kz_);
            ky[i] = dydt(kx_, ky_, kz_);
            kz[i] = dzdt(kx_, ky_, kz_);
        }
        // (8)
        x += (kx[0] + 2*kx[1] + 2*kx[2] + kx[3]) * (h/6.0);
        y += (ky[0] + 2*ky[1] + 2*ky[2] + ky[3]) * (h/6.0);
        z += (kz[0] + 2*kz[1] + 2*kz[2] + kz[3]) * (h/6.0);

        outfile << dt << "\t" << std::setprecision(10) << x << "\t" << std::setprecision(10) << y << "\t" << std::setprecision(10) << z << std::endl; // (9)
    }
    outfile.close(); // (10)
}

// Declaración de métodos basados en las ecuaciones de Lorenz.

double Lorenz::dxdt(double x, double y, double z) {
    return s*(y - x); // dx/dt = s*(y - x)
}

double Lorenz::dydt(double x, double y, double z) {
    return x*(r - z) - y; // dy/dt = x*(r - z) - y
}

double Lorenz::dzdt(double x, double y, double z) {
    return x*y - b*z; // dz/dt = x*y - b*z
}

// Función principal del código.

int main() {
    double x0, y0, z0, s, r, b, t; // Declaración de variables.
    const double h = 0.01; // Declaración de la constante paso h.

    int option = -1;

    // Menú del programa

    std::cout << "Bienvenido al programa" << std::endl << std::endl;

    while (true)
    {
        std::cout << "1. Atractor de Lorenz según la literatura (no inserción de parámetros)." << std::endl;
        std::cout << "2. Única impresión de datos e imágenes (inserción de parámetros)." << std::endl;
        std::cout << "0. Salir." << std::endl << std::endl;
        std::cout << "Seleccione la opción que desea: ";
        std::cin >> option;

        if (option == 1){
            Lorenz lorenzreal(-1.3560, -2.492152, 12.317410, 10.0, 28.0, 8.0/3.0);
            lorenzreal.run(h, 200);
            std::cout << std::endl << std::endl << std::endl << "Los parámetros fueron: x0 = -1.3560, y0 = -2.492152, z0 = 12.317410, sigma = 10.0, rho = 28.0 y b = 8/3." << std::endl;
            break;
        } else if (option == 2){
            std::cout << std::endl << std::endl << std::endl << "Indique la condición inicial para x (x0) = ";
            std::cin >> x0;
            std::cout << "Indique la condición inicial para y (y0) = ";
            std::cin >> y0;
            std::cout << "Indique la condición inicial para z (z0) = ";
            std::cin >> z0;
            std::cout << "Indique el parámetro sigma (s) = ";
            std::cin >> s;
            std::cout << "Indique el parámetro rho (r) = ";
            std::cin >> r;
            std::cout << "Indique el parámetro b (b) = ";
            std::cin >> b;
            std::cout << "Indique el tiempo de ejecución (t) = ";
            std::cin >> t;
            Lorenz lorenz(x0, y0, z0, s, r, b);
            lorenz.run(h,t);
            break;
        } else if (option == 0){
            std::cout << std::endl << "Gracias por ejecutar, hasta pronto..." << std::endl;
            return 0;
        } else {
            std::cout << std::endl << "¡Seleccione una opción correcta!" << std::endl;
        }
    }
    return 0;
}