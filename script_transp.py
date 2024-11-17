import random
import string

def generar_cadenas_intercaladas(nombre_archivo, longitud):
    # Selecciona dos caracteres aleatorios distintos
    caracteres = random.sample(string.ascii_lowercase, 2)
    caracter1, caracter2 = caracteres[0], caracteres[1]

    # Genera la primera cadena alternando los caracteres comenzando con `caracter1`
    cadena1 = ''.join([caracter1 if i % 2 == 0 else caracter2 for i in range(longitud)])
    
    # Genera la segunda cadena alternando los caracteres comenzando con `caracter2`
    cadena2 = ''.join([caracter2 if i % 2 == 0 else caracter1 for i in range(longitud)])
    
    # Escribe las cadenas en el archivo especificado
    with open(nombre_archivo, 'w') as file:
        file.write(f"{cadena1}\n")
        file.write(f"{cadena2}\n")
    

# Ejemplo de uso
generar_cadenas_intercaladas("cadenas_transposición.txt", 10)
