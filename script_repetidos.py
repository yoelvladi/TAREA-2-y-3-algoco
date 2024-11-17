import random
import string

def generar_cadenas_con_repetidos(nombre_archivo, size1, size2):
    def generar_cadena_con_repetidos(size):
        cadena = []
        i = 0
        while i < size:
            # Decide aleatoriamente si agregar un carácter repetido o uno único
            if random.choice([True, False]) and i < size - 1:
                # Generar un carácter repetido (2-3 veces consecutivas)
                char = random.choice(string.ascii_lowercase)
                repeticiones = random.randint(2, 3)
                cadena.extend(char * min(repeticiones, size - i))  # Evita exceder el tamaño
                i += repeticiones
            else:
                # Agregar un carácter único
                cadena.append(random.choice(string.ascii_lowercase))
                i += 1
        return ''.join(cadena[:size])
    
    # Función para encontrar subcadenas de caracteres repetidos consecutivos
    def obtener_subcadenas_repetidas(cadena):
        subcadenas_repetidas = []
        subcadena_actual = cadena[0]
        
        for i in range(1, len(cadena)):
            if cadena[i] == cadena[i - 1]:
                subcadena_actual += cadena[i]
            else:
                if len(subcadena_actual) > 1:
                    subcadenas_repetidas.append(subcadena_actual)
                subcadena_actual = cadena[i]
        
        if len(subcadena_actual) > 1:
            subcadenas_repetidas.append(subcadena_actual)
        
        return subcadenas_repetidas

    # Genera la primera cadena y obtiene las subcadenas repetidas
    cadena1 = generar_cadena_con_repetidos(size1)
    subcadenas_repetidas = obtener_subcadenas_repetidas(cadena1)

    # Genera la segunda cadena sin considerar las repeticiones inicialmente
    cadena2 = list(generar_cadena_con_repetidos(size2))

    # Inserta las subcadenas repetidas en posiciones aleatorias de la segunda cadena
    for subcadena in subcadenas_repetidas:
        pos_insercion = random.randint(0, max(0, len(cadena2) - len(subcadena)))
        cadena2[pos_insercion:pos_insercion + len(subcadena)] = subcadena

    # Convierte la lista en una cadena final
    cadena2 = ''.join(cadena2)

    # Escribe las cadenas en el archivo especificado
    with open(nombre_archivo, 'w') as file:
        file.write(f"{cadena1}\n")
        file.write(f"{cadena2}\n")

    print(f"Cadena 1: {cadena1}")
    print(f"Cadena 2: {cadena2}")

# Ejemplo de uso
generar_cadenas_con_repetidos("cadenas_repetidas.txt", 8, 8)
