# Obra Social - Herencia Total

## Respuestas Teóricas

### ¿Qué ventajas tiene utilizar STL?

STL (Standard Template Library) ofrece las siguientes ventajas:

1. **Reutilización de código**: Provee contenedores (vector, map, set) y algoritmos (sort, find, for_each) ya probados y optimizados, evitando tener que implementarlos desde cero.

2. **Eficiencia**: Los algoritmos de STL están implementados con las mejores complejidades algorítmicas conocidas. Por ejemplo, `sort` usa introsort con complejidad O(n log n).

3. **Genericidad**: Al usar templates, los contenedores y algoritmos funcionan con cualquier tipo de dato (int, string, objetos propios), lo que los hace muy flexibles.

4. **Mantenibilidad**: El código es más legible y fácil de mantener porque se usan funciones estándar reconocidas por cualquier programador de C++.

5. **Menos errores**: Al usar contenedores como `vector` en lugar de arrays dinámicos manuales, se evitan errores comunes de manejo de memoria.

### ¿Para qué nos sirven los iterators?

Los iterators (iteradores) son objetos que permiten recorrer los elementos de un contenedor de manera uniforme. Sirven para:

1. **Acceso secuencial**: Permiten recorrer los elementos de cualquier contenedor (vector, list, map) de forma uniforme, sin importar la implementación interna del contenedor.

2. **Compatibilidad con algoritmos STL**: Los algoritmos como `sort`, `find`, `copy`, `for_each` reciben iteradores como parámetros. Los iteradores son el "puente" entre los contenedores y los algoritmos.

3. **Abstracción**: Ocultan la estructura interna del contenedor. Se puede cambiar de vector a list sin modificar el código que usa iteradores.

4. **Rangos**: Permiten definir rangos de elementos (begin a end) para operar sobre subconjuntos del contenedor.

5. **Inserción/eliminación**: Iteradores especiales como `back_inserter` permiten insertar elementos al final de un contenedor durante operaciones como `copy` o `transform`.
