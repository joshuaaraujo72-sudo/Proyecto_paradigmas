import Data.List.Split (splitOn)

type Historial = (String, String, Float)

listaNotas :: [Historial] -> String -> [Historial] 
listaNotas historiales nombre = filter (\(x,_,_) -> x == nombre) historiales

calcularPromedio :: [Historial] -> String -> Float
calcularPromedio historiales nombre = 
    (foldr (\(_,_,z) acum -> acum + z) 0 (listaNotas historiales nombre) ) 
    / fromIntegral (length (listaNotas historiales nombre))

cursosAprobados :: [Historial] -> String -> [String]
cursosAprobados historiales nombre =
    map (\(_,y,_) -> y) (filter (\(_,_,z) -> z >= 11) (listaNotas historiales nombre))

cursosDesaprobados :: [Historial] -> String -> [String]
cursosDesaprobados historiales nombre =
    map (\(_,y,_) -> y) (filter (\(_,_,z) -> z < 11) (listaNotas historiales nombre))

clasificarRendimiento :: [Historial] -> String -> String
clasificarRendimiento historiales nombre
    | calcularPromedio historiales nombre >= 16 = "Alto"
    | calcularPromedio historiales nombre >= 13 = "Medio"
    | otherwise = "Bajo"

generarRecomendacion :: [Historial] -> String -> String
generarRecomendacion historiales nombre
    | calcularPromedio historiales nombre >= 14 = "El estudiante tiene buen rendimiento. Puede llevar cursos de mayor dificultad."
    | otherwise = "Se recomienda reforzar cursos base antes de llevar cursos avanzados."

cantidadAprobados :: [Historial] -> String -> Int
cantidadAprobados historiales nombre = length (cursosAprobados historiales nombre)

cantidadDesaprobados :: [Historial] -> String -> Int
cantidadDesaprobados historiales nombre = length (cursosDesaprobados historiales nombre)

convertirHistorial :: String -> Historial
convertirHistorial linea =
    let [codigo, curso, nota] = splitOn "," linea
    in (codigo, curso, read nota)

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
    putStrLn ("Recomendación: " ++ generarRecomendacion historial estudiante)
    putStrLn ("Cantidad de aprobados: " ++ show (cantidadAprobados historial estudiante))
    putStrLn ("Cantidad de desaprobados: " ++ show (cantidadDesaprobados historial estudiante))