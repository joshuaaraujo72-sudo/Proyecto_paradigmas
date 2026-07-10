#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Curso
{
    string codigo;
    string nombre;
    string area;
    int creditos;
};

struct Prerrequisito
{
    string curso;
    string prerrequisito;
};

struct Historial
{
    string estudiante;
    string codigoCurso;
    int nota;
};

struct Interes
{
    string estudiante;
    string area;
};

vector<Curso> cursos;
vector<Prerrequisito> prerrequisitos;
vector<Historial> historial;
vector<Interes> intereses;

// INICIO CURSOS
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
// FIN CURSOS

// INICIO PRERREQUISITOS
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
// FIN PRERREQUISITOS

// TODO HISTORIAL
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
// FIN HISTORIAL

// TODO INTERESES DE ALUMNOS
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
// FIN INTERESES DE ALUMNOS

// APROBADOS
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

// DESAPROBADOS
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
        cout << "No hay cursos aprobados para ese estudiante." << endl;
    }
}

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