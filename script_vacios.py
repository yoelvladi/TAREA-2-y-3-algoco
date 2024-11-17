import random
import string

def generar_cadenas_vacia_y_aleatoria(nombre_archivo, longitud, primera_vacia=True):
    # Genera una cadena aleatoria de longitud especificada
    cadena_aleatoria = ''.join(random.choice(string.ascii_lowercase) for _ in range(longitud))
    
    # Asigna la cadena vacía y la aleatoria según el parámetro `primera_vacia`
    if primera_vacia:
        cadena1 = ''
        cadena2 = cadena_aleatoria
    else:
        cadena1 = cadena_aleatoria
        cadena2 = ''
    
    # Escribe las cadenas en el archivo especificado
    with open(nombre_archivo, 'w') as file:
        file.write(f"'{cadena1}'\n")
        file.write(f"'{cadena2}'\n")
    

# Ejemplo de uso
generar_cadenas_vacia_y_aleatoria("cadenas_vacia_y_aleatoria.txt", 10, primera_vacia=True)
