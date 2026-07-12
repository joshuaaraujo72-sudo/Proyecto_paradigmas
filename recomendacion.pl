/*
   Sistema Inteligente de Recomendacion Academica - Modulo Prolog (paradigma logico)
   Lee los 4 archivos CSV generados por el modulo en C++, construye la base de
   conocimiento (hechos) y define reglas logicas para consultar cursos aprobados,
   cursos disponibles, cursos bloqueados y recomendaciones por interes.

   Uso (SWI-Prolog, desde la carpeta del proyecto):
     swipl recomendacion.pl
   Consultas de ejemplo:
     ?- aprobado(estudiante1, ip101).
     ?- puede_llevar(estudiante1, pw101).
     ?- recomendar_curso(estudiante1, Cursos).
     ?- curso_bloqueado(estudiante1, Cursos).
     ?- recomendar_por_interes(estudiante1, Curso).
     ?- resumen(estudiante1).
*/

:- use_module(library(csv)).

% Hechos dinamicos que forman la base de conocimiento (se cargan desde los CSV)
:- dynamic curso/4.          % curso(Codigo, Nombre, Area, Creditos)
:- dynamic prerrequisito/2.  % prerrequisito(Curso, Prerrequisito)
:- dynamic nota/3.           % nota(Estudiante, Curso, Nota)
:- dynamic interes/2.        % interes(Estudiante, Area)

% ===== CARGA DE LA BASE DE CONOCIMIENTO DESDE LOS CSV =====

% Convierte un valor del CSV a un atomo en minusculas (para consultas uniformes)
minuscula(Valor, Atomo) :-
    ( number(Valor) -> Atomo = Valor
    ; downcase_atom(Valor, Atomo)
    ).

% Carga cursos.csv y asserta un hecho curso/4 por cada fila
cargar_cursos :-
    csv_read_file('Archivos_CSV/cursos.csv', [_Cabecera | Filas], []),
    forall(member(row(Cod, Nom, Area, Cred), Filas),
           ( minuscula(Cod, C), minuscula(Area, A),
             assertz(curso(C, Nom, A, Cred)) )).

% Carga prerrequisitos.csv y asserta hechos prerrequisito/2
cargar_prerrequisitos :-
    csv_read_file('Archivos_CSV/prerrequisitos.csv', [_Cabecera | Filas], []),
    forall(member(row(Curso, Prerreq), Filas),
           ( minuscula(Curso, C), minuscula(Prerreq, P),
             assertz(prerrequisito(C, P)) )).

% Carga historial.csv y asserta hechos nota/3
cargar_historial :-
    csv_read_file('Archivos_CSV/historial.csv', [_Cabecera | Filas], []),
    forall(member(row(Est, Curso, Nota), Filas),
           ( minuscula(Est, E), minuscula(Curso, C),
             assertz(nota(E, C, Nota)) )).

% Carga intereses.csv y asserta hechos interes/2
cargar_intereses :-
    csv_read_file('Archivos_CSV/intereses.csv', [_Cabecera | Filas], []),
    forall(member(row(Est, Area), Filas),
           ( minuscula(Est, E), minuscula(Area, A),
             assertz(interes(E, A)) )).

% Carga los 4 archivos CSV en la base de conocimiento.
% Primero limpia los hechos anteriores para poder recargar sin duplicados.
cargar_datos :-
    retractall(curso(_, _, _, _)),
    retractall(prerrequisito(_, _)),
    retractall(nota(_, _, _)),
    retractall(interes(_, _)),
    cargar_cursos,
    cargar_prerrequisitos,
    cargar_historial,
    cargar_intereses,
    writeln('Base de conocimiento cargada desde los archivos CSV.').

% ===== REGLAS LOGICAS =====

% Un estudiante aprobo un curso si su nota es mayor o igual a 11
aprobado(Estudiante, Curso) :-
    nota(Estudiante, Curso, Nota),
    Nota >= 11.

% Un estudiante desaprobo un curso si su nota es menor a 11
desaprobado(Estudiante, Curso) :-
    nota(Estudiante, Curso, Nota),
    Nota < 11.

% Un estudiante cumple los prerrequisitos de un curso si aprobo todos ellos
% (si el curso no tiene prerrequisitos, la regla es verdadera)
cumple_prerrequisitos(Estudiante, Curso) :-
    forall(prerrequisito(Curso, Prerreq), aprobado(Estudiante, Prerreq)).

% Un estudiante puede llevar un curso si existe, no lo aprobo aun
% y cumple todos sus prerrequisitos
puede_llevar(Estudiante, Curso) :-
    curso(Curso, _, _, _),
    \+ aprobado(Estudiante, Curso),
    cumple_prerrequisitos(Estudiante, Curso).

% Un curso esta bloqueado para un estudiante si no lo aprobo y
% le falta aprobar al menos un prerrequisito
bloqueado(Estudiante, Curso) :-
    curso(Curso, _, _, _),
    \+ aprobado(Estudiante, Curso),
    prerrequisito(Curso, Prerreq),
    \+ aprobado(Estudiante, Prerreq).

% Recomienda la lista de cursos que el estudiante puede llevar el siguiente ciclo
recomendar_curso(Estudiante, Cursos) :-
    findall(Curso, puede_llevar(Estudiante, Curso), Cursos).

% Lista de cursos bloqueados por falta de prerrequisitos
curso_bloqueado(Estudiante, Cursos) :-
    setof(Curso, bloqueado(Estudiante, Curso), Cursos), !.
curso_bloqueado(_, []).

% Recomienda un curso cuya area coincide con un interes del estudiante,
% que el estudiante no haya aprobado y que pueda llevar
recomendar_por_interes(Estudiante, Curso) :-
    interes(Estudiante, Area),
    curso(Curso, _, Area, _),
    puede_llevar(Estudiante, Curso).

% ===== RESUMEN PARA LA DEMOSTRACION =====

% Muestra el estado academico completo de un estudiante
resumen(Estudiante) :-
    format('===== RESUMEN DE ~w =====~n', [Estudiante]),
    findall(C, aprobado(Estudiante, C), Aprobados),
    format('Cursos aprobados: ~w~n', [Aprobados]),
    findall(C, desaprobado(Estudiante, C), Desaprobados),
    format('Cursos desaprobados: ~w~n', [Desaprobados]),
    recomendar_curso(Estudiante, Disponibles),
    format('Cursos que puede llevar: ~w~n', [Disponibles]),
    curso_bloqueado(Estudiante, Bloqueados),
    format('Cursos bloqueados por prerrequisitos: ~w~n', [Bloqueados]),
    findall(C, recomendar_por_interes(Estudiante, C), PorInteres),
    sort(PorInteres, PorInteresUnicos),
    format('Recomendados segun sus intereses: ~w~n', [PorInteresUnicos]).

% Al consultar este archivo se carga automaticamente la base de conocimiento
:- initialization(cargar_datos).
