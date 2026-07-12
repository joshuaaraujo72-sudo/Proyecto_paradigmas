# Sistema Inteligente de Recomendación Académica

Proyecto del curso Paradigmas de la Programación. Integra tres paradigmas mediante
archivos CSV compartidos en `Archivos_CSV/`:

- **C++** (imperativo): registra cursos, prerrequisitos, historial y áreas de interés,
  y genera los archivos CSV.
- **Haskell** (funcional): lee `historial.csv` y calcula promedio, cursos
  aprobados/desaprobados, rendimiento y una recomendación textual.
- **Prolog** (lógico): lee los 4 CSV y responde consultas sobre cursos aprobados,
  cursos disponibles, cursos bloqueados por prerrequisitos y recomendaciones por interés.

El flujo de trabajo es: primero se ejecuta C++ para generar/actualizar los CSV, y luego
se ejecutan Haskell y Prolog, que solo leen esos archivos.

## Requisitos

- Compilador de C++ (g++, con soporte C++17)
- GHC (Glasgow Haskell Compiler). El módulo solo usa Prelude, sin paquetes externos.
- SWI-Prolog

## 1. Módulo C++

Compilar y ejecutar desde la carpeta `Proyecto_paradigmas`:

```
g++ -std=c++17 -o main main.cpp
./main
```

Muestra un menú por consola para registrar cursos, prerrequisitos, historial e
intereses, y para consultar cursos, historial, aprobados/desaprobados y el reporte
general de un estudiante. Cada registro se guarda automáticamente en
`Archivos_CSV/*.csv`.

## 2. Módulo Haskell

Compilar y ejecutar:

```
ghc -o recomendacion_hs main.hs
./recomendacion_hs
```

(o, si se prefiere sin compilar: `runghc main.hs`)

Lee `Archivos_CSV/historial.csv` y muestra el promedio, los cursos
aprobados/desaprobados, la clasificación de rendimiento (Alto/Medio/Bajo) y una
recomendación para `estudiante1`. Para analizar otro estudiante, cambiar el valor de
`estudiante` en la función `main` de `main.hs`.

## 3. Módulo Prolog

Ejecutar desde la carpeta `Proyecto_paradigmas`:

```
swipl recomendacion.pl
```

Al cargar el archivo se leen automáticamente los 4 CSV y se construye la base de
conocimiento. Luego se pueden hacer consultas en la consola de Prolog, por ejemplo:

```prolog
?- aprobado(estudiante1, ip101).
?- puede_llevar(estudiante1, pw101).
?- recomendar_curso(estudiante1, Cursos).
?- curso_bloqueado(estudiante1, Cursos).
?- recomendar_por_interes(estudiante1, Curso).
?- resumen(estudiante1).
```

## Estructura de archivos

```
main.cpp                 Módulo C++
main.hs                  Módulo Haskell
recomendacion.pl         Módulo Prolog
Archivos_CSV/
  cursos.csv
  prerrequisitos.csv
  historial.csv
  intereses.csv
```
