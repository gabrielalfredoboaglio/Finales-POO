# Sistema de Análisis de Comentarios de Productos

## Diseño del Sistema

### Clases Implementadas

1. **Comentario**: Representa un comentario con texto, puntaje y comentarios hijos (estructura jerárquica).
   - Relación con comentarios hijos: **Composición** (se destruyen en el destructor)

2. **Producto**: Representa un producto con nombre y comentarios.
   - Relación con comentarios: **Composición** (se destruyen en el destructor)

3. **Gestora**: Gestiona todos los productos, lectura de archivos y operaciones STL.

### Relaciones

- **Composición**: Producto tiene comentarios (vector<Comentario*>)
- **Composición**: Comentario tiene comentarios hijos (vector<Comentario*>)
- **No hay herencia**: Todos los comentarios son del mismo tipo, solo cambia la jerarquía

### Estructura de Archivos

- **comentarios.txt**: Archivo de texto con formato jerárquico usando guiones
- **resultados.dat**: Archivo binario con resultados de las consultas

## Respuestas Teóricas

### ¿Qué ventajas y desventajas tiene la recursividad en C++?

#### Ventajas:

1. **Código más claro**: Para problemas recursivos naturales (árboles, listas enlazadas), la recursión es más legible que iteración.
2. **Solución natural**: Algunos problemas se resuelven de forma más intuitiva con recursión.
3. **Menos variables temporales**: No necesitas mantener estado en variables auxiliares.

#### Desventajas:

1. **Stack overflow**: Puede causar desbordamiento de pila con estructuras muy profundas.
2. **Rendimiento**: Cada llamada recursiva tiene overhead (crear stack frame).
3. **Memoria**: Consume más memoria por las llamadas en la pila.
4. **Depuración**: Puede ser más difícil depurar código recursivo.

### ¿Por qué C++ necesita de herencia para implementar el polimorfismo?

C++ necesita herencia para el polimorfismo porque:

1. **Jerarquía de tipos**: La herencia establece la relación "es-un" entre clases, creando una jerarquía necesaria para el polimorfismo.
2. **Métodos virtuales**: Los métodos virtuales en la clase base permiten el enlace dinámico (dynamic binding).
3. **Punteros base**: Solo con herencia puedes usar punteros a la clase base que apunten a objetos derivados.
4. **Tabla de métodos virtuales (vtable)**: El compilador crea una tabla que permite resolver en tiempo de ejecución qué método llamar según el tipo real del objeto.

Sin herencia, no habría jerarquía de tipos y el polimorfismo no sería posible. El polimorfismo requiere que objetos de diferentes tipos puedan ser tratados a través de una interfaz común (la clase base), lo cual solo es posible con herencia.

## Libre: Comentario puede responder a varios comentarios

Para el ejercicio libre, se modifica la clase `Comentario` para que pueda tener múltiples comentarios padres (responder a varios comentarios):

```cpp
class Comentario {
private:
    vector<Comentario*> comentariosPadres;  // Puede responder a varios
    vector<Comentario*> comentariosHijos;   // Puede tener varios hijos
    // ...
};
```

Esto cambia de una estructura jerárquica (árbol) a una estructura de grafo, donde un comentario puede tener múltiples padres.
