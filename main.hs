-- Sistema Inteligente de Recomendacion Academica - Modulo Haskell (paradigma funcional)
-- Lee Archivos_CSV/historial.csv (generado por el modulo en C++) y procesa las notas
-- de un estudiante: promedio, cursos aprobados/desaprobados, rendimiento y recomendacion.
-- Solo usa Prelude, sin dependencias externas.

-- Separa una cadena por comas, por ejemplo "a,b,c" -> ["a","b","c"]
splitComa :: String -> [String]
splitComa cadena = case break (== ',') cadena of
    (antes, [])       -> [antes]
    (antes, _:despues) -> antes : splitComa despues

-- Una fila del historial: (estudiante, codigoCurso, nota)
type Historial = (String, String, Float)

-- Filtra las filas del historial que pertenecen a un estudiante
listaNotas :: [Historial] -> String -> [Historial]
listaNotas historiales nombre = filter (\(x,_,_) -> x == nombre) historiales

-- Promedio de las notas de un estudiante (suma con foldr / cantidad de cursos)
calcularPromedio :: [Historial] -> String -> Float
calcularPromedio historiales nombre =
    (foldr (\(_,_,z) acum -> acum + z) 0 (listaNotas historiales nombre) )
    / fromIntegral (length (listaNotas historiales nombre))

-- Codigos de los cursos aprobados (nota >= 11) de un estudiante
cursosAprobados :: [Historial] -> String -> [String]
cursosAprobados historiales nombre =
    map (\(_,y,_) -> y) (filter (\(_,_,z) -> z >= 11) (listaNotas historiales nombre))

-- Codigos de los cursos desaprobados (nota < 11) de un estudiante
cursosDesaprobados :: [Historial] -> String -> [String]
cursosDesaprobados historiales nombre =
    map (\(_,y,_) -> y) (filter (\(_,_,z) -> z < 11) (listaNotas historiales nombre))

-- Clasifica el rendimiento segun el promedio: Alto (>=16), Medio (>=13), Bajo (resto)
clasificarRendimiento :: [Historial] -> String -> String
clasificarRendimiento historiales nombre
    | calcularPromedio historiales nombre >= 16 = "Alto"
    | calcularPromedio historiales nombre >= 13 = "Medio"
    | otherwise = "Bajo"

-- Genera un mensaje de recomendacion consistente con clasificarRendimiento:
-- Alto/Medio pueden avanzar con cursos de mayor dificultad, Bajo debe reforzar
generarRecomendacion :: [Historial] -> String -> String
generarRecomendacion historiales nombre =
    case clasificarRendimiento historiales nombre of
        "Bajo" -> "Se recomienda reforzar cursos base antes de llevar cursos avanzados."
        _      -> "El estudiante tiene buen rendimiento. Puede llevar cursos de mayor dificultad."

-- Cantidad de cursos aprobados de un estudiante
cantidadAprobados :: [Historial] -> String -> Int
cantidadAprobados historiales nombre = length (cursosAprobados historiales nombre)

-- Cantidad de cursos desaprobados de un estudiante
cantidadDesaprobados :: [Historial] -> String -> Int
cantidadDesaprobados historiales nombre = length (cursosDesaprobados historiales nombre)

-- Convierte una linea "estudiante,codigoCurso,nota" del CSV en una tupla Historial
convertirHistorial :: String -> Historial
convertirHistorial linea =
    let [estudiante, curso, nota] = splitComa linea
    in (estudiante, curso, read nota)

-- Lee historial.csv y descarta la fila de encabezado
leerHistorial :: IO [Historial]
leerHistorial = do
    contenido <- readFile "Archivos_CSV/historial.csv"
    return (map convertirHistorial (tail (lines contenido)))

main = do
    historial <- leerHistorial

    let estudiante = "estudiante1"

    putStrLn ("Estudiante: " ++ estudiante)
    putStrLn ("Promedio: " ++ show (calcularPromedio historial estudiante))
    putStrLn ("Cursos aprobados: " ++ show (cursosAprobados historial estudiante))
    putStrLn ("Cursos desaprobados: " ++ show (cursosDesaprobados historial estudiante))
    putStrLn ("Rendimiento: " ++ clasificarRendimiento historial estudiante)
    putStrLn ("Recomendacion: " ++ generarRecomendacion historial estudiante)
    putStrLn ("Cantidad de aprobados: " ++ show (cantidadAprobados historial estudiante))
    putStrLn ("Cantidad de desaprobados: " ++ show (cantidadDesaprobados historial estudiante))
