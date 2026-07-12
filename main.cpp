/*
   Sistema Inteligente de Recomendacion Academica - Modulo C++ (paradigma imperativo)
   Registra cursos, prerrequisitos, historial academico e intereses del estudiante,
   los guarda en archivos CSV (Archivos_CSV/) y permite consultarlos por consola.
   Estos CSV son luego leidos por los modulos en Haskell y Prolog.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Informacion de un curso del catalogo
struct Curso
{
    string codigo;
    string nombre;
    string area;
    int creditos;
};

// Relacion curso -> prerrequisito que debe estar aprobado antes de llevarlo
struct Prerrequisito
{
    string curso;
    string prerrequisito;
};

// Nota obtenida por un estudiante en un curso
struct Historial
{
    string estudiante;
    string codigoCurso;
    int nota;
};

// Area academica de interes de un estudiante
struct Interes
{
    string estudiante;
    string area;
};

// Datos en memoria, cargados desde los CSV al iniciar y actualizados con cada registro
vector<Curso> cursos;
vector<Prerrequisito> prerrequisitos;
vector<Historial> historial;
vector<Interes> intereses;

// ===== CURSOS =====

// Escribe todo el vector de cursos en Archivos_CSV/cursos.csv
void guardarCursosCSV()
{
    ofstream archivo("Archivos_CSV/cursos.csv");

    archivo << "codigo,nombre,area,creditos\n";

    for (int i = 0; i < cursos.size(); i++)
    {
        archivo << cursos[i].codigo << ",";
        archivo << cursos[i].nombre << ",";
        archivo << cursos[i].area << ",";
        archivo << cursos[i].creditos << "\n";
    }

    archivo.close();

    cout << "\nArchivo cursos.csv guardado correctamente.\n";
}

// Pide los datos de un curso por consola, lo agrega al vector y lo persiste en CSV
void registrarCurso()
{
    Curso nuevo;
    cout << "\n===== REGISTRAR CURSO =====" << endl;

    cout << "Codigo: ";
    cin >> nuevo.codigo;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Area: ";
    getline(cin, nuevo.area);

    cout << "Creditos: ";
    cin >> nuevo.creditos;

    cursos.push_back(nuevo);

    guardarCursosCSV();
}

// Imprime por consola todos los cursos cargados en memoria
void mostrarCursos()
{
    cout << "\n===== CURSOS REGISTRADOS =====";

    if (cursos.empty())
    {
        cout << "No hay cursos registrados." << endl;
        return;
    }

    for (int i = 0; i < cursos.size(); i++)
    {
        cout << "\nCurso " << i + 1 << endl;
        cout << "Codigo: " << cursos[i].codigo << endl;
        cout << "Nombre: " << cursos[i].nombre << endl;
        cout << "Area: " << cursos[i].area << endl;
        cout << "Creditos: " << cursos[i].creditos << endl;
    }
}

// Carga cursos.csv en el vector cursos al iniciar el programa
void leerCursosCSV()
{
    ifstream archivo("Archivos_CSV/cursos.csv");

    if (!archivo.is_open())
    {
        return;
    }

    string linea;

    getline(archivo, linea); // Salta el encabezado

    while (getline(archivo, linea))
    {
        Curso c;

        stringstream ss(linea);

        string creditos;

        getline(ss, c.codigo, ',');
        getline(ss, c.nombre, ',');
        getline(ss, c.area, ',');
        getline(ss, creditos, ',');

        c.creditos = stoi(creditos);

        cursos.push_back(c);
    }

    archivo.close();
}

// ===== PRERREQUISITOS =====

// Escribe todo el vector de prerrequisitos en Archivos_CSV/prerrequisitos.csv
void guardarPrerrequisitosCSV()
{
    ofstream archivo("Archivos_CSV/prerrequisitos.csv");

    archivo << "curso,prerrequisito\n";

    for (int i = 0; i < prerrequisitos.size(); i++)
    {
        archivo << prerrequisitos[i].curso << ",";
        archivo << prerrequisitos[i].prerrequisito << "\n";
    }

    archivo.close();

    cout << "\nArchivo prerrequisitos.csv guardado correctamente.\n";
}

// Pide un par (curso, prerrequisito) por consola y lo persiste en CSV
void registrarPrerrequisito()
{
    Prerrequisito nuevo;

    cout << "\n===== REGISTRAR PRERREQUISITO =====" << endl;

    cout << "Curso: ";
    cin >> nuevo.curso;

    cout << "Prerrequisito: ";
    cin >> nuevo.prerrequisito;

    prerrequisitos.push_back(nuevo);

    guardarPrerrequisitosCSV();

    cout << "\nPrerrequisito registrado correctamente.\n";
}

// Carga prerrequisitos.csv en el vector prerrequisitos al iniciar el programa
void leerPrerrequisitosCSV()
{
    ifstream archivo("Archivos_CSV/prerrequisitos.csv");

    if (!archivo.is_open())
        return;

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        Prerrequisito p;

        stringstream ss(linea);

        getline(ss, p.curso, ',');
        getline(ss, p.prerrequisito, ',');

        prerrequisitos.push_back(p);
    }

    archivo.close();
}

// ===== HISTORIAL ACADEMICO =====

// Escribe todo el vector de historial en Archivos_CSV/historial.csv
void guardarHistorialCSV()
{
    ofstream archivo("Archivos_CSV/historial.csv");

    archivo << "estudiante,codigoCurso,nota\n";

    for (int i = 0; i < historial.size(); i++)
    {
        archivo << historial[i].estudiante << ",";
        archivo << historial[i].codigoCurso << ",";
        archivo << historial[i].nota << "\n";
    }

    archivo.close();

    cout << "\nArchivo historial.csv guardado correctamente.\n";
}

// Pide estudiante, curso y nota por consola (valida que la nota este en 0-20)
// y persiste el registro en CSV. Nota >= 11 se considera aprobado.
void registrarHistorial()
{
    Historial nuevo;

    cout << "\n===== REGISTRAR HISTORIAL =====" << endl;

    cout << "Estudiante: ";
    cin >> nuevo.estudiante;

    cout << "Codigo del curso: ";
    cin >> nuevo.codigoCurso;

    do
    {
        cout << "Nota: ";
        cin >> nuevo.nota;

        if (nuevo.nota < 0 || nuevo.nota > 20)
        {
            cout << "La nota debe estar entre 0 y 20.\n";
        }

    } while (nuevo.nota < 0 || nuevo.nota > 20);

    historial.push_back(nuevo);

    guardarHistorialCSV();

    cout << "\nHistorial registrado correctamente.\n";
}

// Imprime por consola todos los registros de historial cargados en memoria
void mostrarHistorial()
{
    cout << "\n===== HISTORIAL =====";

    if (historial.empty())
    {
        cout << "No hay historial registrado.\n";
        return;
    }

    for (int i = 0; i < historial.size(); i++)
    {
        cout << "\nRegistro " << i + 1 << endl;
        cout << "Estudiante: " << historial[i].estudiante << endl;
        cout << "Curso: " << historial[i].codigoCurso << endl;
        cout << "Nota: " << historial[i].nota << endl;
    }
}

// Carga historial.csv en el vector historial al iniciar el programa
void leerHistorialCSV()
{
    ifstream archivo("Archivos_CSV/historial.csv");

    if (!archivo.is_open())
        return;

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        Historial h;

        stringstream ss(linea);

        string nota;

        getline(ss, h.estudiante, ',');
        getline(ss, h.codigoCurso, ',');
        getline(ss, nota, ',');

        h.nota = stoi(nota);

        historial.push_back(h);
    }

    archivo.close();
}

// ===== INTERESES DEL ESTUDIANTE =====

// Escribe todo el vector de intereses en Archivos_CSV/intereses.csv
void guardarInteresesCSV()
{
    ofstream archivo("Archivos_CSV/intereses.csv");

    archivo << "estudiante,area\n";

    for (int i = 0; i < intereses.size(); i++)
    {
        archivo << intereses[i].estudiante << ",";
        archivo << intereses[i].area << "\n";
    }

    archivo.close();

    cout << "\nArchivo intereses.csv guardado correctamente.\n";
}

// Pide un area de interes de un estudiante por consola y la persiste en CSV
void registrarInteres()
{
    Interes nuevo;

    cout << "\n===== REGISTRAR INTERES =====" << endl;

    cout << "Estudiante: ";
    cin >> nuevo.estudiante;

    cout << "Area: ";
    cin.ignore();
    getline(cin, nuevo.area);

    intereses.push_back(nuevo);

    guardarInteresesCSV();

    cout << "\nInteres registrado correctamente.\n";
}

// Carga intereses.csv en el vector intereses al iniciar el programa
void leerInteresesCSV()
{
    ifstream archivo("Archivos_CSV/intereses.csv");

    if (!archivo.is_open())
        return;

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        Interes in;

        stringstream ss(linea);

        getline(ss, in.estudiante, ',');
        getline(ss, in.area, ',');

        intereses.push_back(in);
    }

    archivo.close();
}

// ===== CONSULTAS Y REPORTES =====

// Muestra los cursos que un estudiante aprobo (nota >= 11)
void mostrarCursosAprobados()
{
    string estudiante;
    bool encontrado = false;

    cout << "\nIngrese el nombre del estudiante: ";
    cin >> estudiante;

    cout << "\n===== CURSOS APROBADOS DEL ESTUDIANTE: " << estudiante << " =====" << endl;

    for (int i = 0; i < historial.size(); i++)
    {
        if (historial[i].estudiante == estudiante && historial[i].nota >= 11)
        {
            cout << historial[i].codigoCurso << " --> Nota: " << historial[i].nota << endl;

            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "No hay cursos aprobados para ese estudiante." << endl;
    }
}

// Muestra los cursos que un estudiante desaprobo (nota < 11)
void mostrarCursosDesaprobados()
{
    string estudiante;
    bool encontrado = false;

    cout << "\nIngrese el nombre del estudiante: ";
    cin >> estudiante;

    cout << "\n===== CURSOS DESAPROBADOS DEL ESTUDIANTE: " << estudiante << " =====" << endl;

    for (int i = 0; i < historial.size(); i++)
    {
        if (historial[i].estudiante == estudiante && historial[i].nota < 11)
        {
            cout << historial[i].codigoCurso << " --> Nota: " << historial[i].nota << endl;

            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "No hay cursos desaprobados para ese estudiante." << endl;
    }
}

// Devuelve el nombre del curso dado su codigo (cadena vacia si no existe)
string buscarCurso(string codCurso)
{
    string nombre;
    for (int i = 0; i < cursos.size(); i++)
    {
        if(cursos[i].codigo == codCurso){
            nombre = cursos[i].nombre;
        }
    }
    return nombre;
}

// Calcula y muestra el resumen academico de un estudiante: promedio, cantidad
// de cursos aprobados/desaprobados y los cursos de mayor y menor nota
void reporteGeneral()
{
    string estudiante;

    cout << "\nIngrese el nombre del estudiante: ";
    cin >> estudiante;

    int suma = 0;
    int cantidad = 0;
    int aprobados = 0;
    int desaprobados = 0;

    int mayorNota = -1;
    int menorNota = 21;

    string cursoMayor;
    string cursoMenor;

    for (int i = 0; i < historial.size(); i++)
    {
        if (historial[i].estudiante == estudiante)
        {
            suma += historial[i].nota;
            cantidad++;

            if (historial[i].nota >= 11)
            {
                aprobados++;
            }
            else
            {
                desaprobados++;
            }

            if (historial[i].nota > mayorNota)
            {
                mayorNota = historial[i].nota;
                cursoMayor = historial[i].codigoCurso;
            }

            if (historial[i].nota < menorNota)
            {
                menorNota = historial[i].nota;
                cursoMenor = historial[i].codigoCurso;
            }
        }
    }

    string nombreCursoMayor = buscarCurso(cursoMayor);
    string nombreCursoMenor = buscarCurso(cursoMenor);

    if (cantidad == 0)
    {
        cout << "El estudiante no existe.\n";
        return;
    }

    double promedio = (double)suma / cantidad;

    cout << "\n===== REPORTE GENERAL =====\n";

    cout << "Estudiante: " << estudiante << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Cursos aprobados: " << aprobados << endl;
    cout << "Cursos desaprobados: " << desaprobados << endl;
    cout << "Mayor nota: " << nombreCursoMayor << " (" << mayorNota << ")" << endl;
    cout << "Menor nota: " << nombreCursoMenor << " (" << menorNota << ")" << endl;
}

// Carga los CSV existentes y muestra el menu principal hasta que el usuario elija salir
int main()
{
    leerCursosCSV();
    leerPrerrequisitosCSV();
    leerHistorialCSV();
    leerInteresesCSV();

    int opcion;

    do
    {
        cout << "\n===== SISTEMA DE RECOMENDACION ACADEMICA =====" << endl;
        cout << "1. Registrar curso" << endl;
        cout << "2. Registrar prerrequisito" << endl;
        cout << "3. Registrar historial" << endl;
        cout << "4. Registrar interes" << endl;
        cout << "5. Mostrar cursos" << endl;
        cout << "6. Mostrar historial" << endl;
        cout << "7. Mostrar cursos aprobados" << endl;
        cout << "8. Mostrar cursos desaprobados" << endl;
        cout << "9. Reporte general de alumno" << endl;
        cout << "0. Salir" << endl;

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrarCurso();
            break;

        case 2:
            registrarPrerrequisito();
            break;

        case 3:
            registrarHistorial();
            break;

        case 4:
            registrarInteres();
            break;

        case 5:
            mostrarCursos();
            break;

        case 6:
            mostrarHistorial();
            break;

        case 7:
            mostrarCursosAprobados();
            break;

        case 8:
            mostrarCursosDesaprobados();
            break;

        case 9:
            reporteGeneral();
            break;

        case 0:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);

    return 0;
}