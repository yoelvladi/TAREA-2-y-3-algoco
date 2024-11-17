import random
import string

def generar_cadenas(nombre_archivo, size1, size2):
    # Genera dos cadenas aleatorias de tamaño `size1` y `size2`
    cadena1 = ''.join(random.choice(string.ascii_lowercase) for _ in range(size1))
    cadena2 = ''.join(random.choice(string.ascii_lowercase) for _ in range(size2))
    
    # Escribe las cadenas en el archivo
    with open(nombre_archivo, 'w') as file:
        file.write(f"{cadena1}\n{cadena2}")

# Ejemplo de uso
generar_cadenas("cadenas_aleatorias.txt", 15, 15)
