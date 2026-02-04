# Sistema de Encuestas

## Respuestas Teóricas

### (20 puntos) Explique porque son necesarias las clases template. ¿Cuándo las utilizaría? ¿Cuáles son sus ventajas y desventajas?

#### ¿Por qué son necesarias las clases template?

Las clases template son necesarias porque permiten crear código genérico y reutilizable que funciona con diferentes tipos de datos sin necesidad de duplicar código. Esto es fundamental para:

1. **Reutilización de código**: Permite escribir una sola implementación que funciona con múltiples tipos de datos, evitando la duplicación de código.

2. **Type safety**: Proporciona seguridad de tipos en tiempo de compilación, detectando errores antes de la ejecución.

3. **Eficiencia**: No hay overhead en tiempo de ejecución (a diferencia de las clases base polimórficas), ya que el compilador genera código específico para cada tipo usado.

4. **Flexibilidad**: Permite crear estructuras de datos y algoritmos genéricos que pueden trabajar con cualquier tipo que cumpla ciertos requisitos.

5. **Abstracción**: Permite abstraer la lógica de los tipos específicos, enfocándose en el comportamiento común.

#### ¿Cuándo las utilizaría?

Las clases template se utilizan cuando:

1. **Estructuras de datos genéricas**: Cuando necesitas crear contenedores que funcionen con diferentes tipos (ej: `vector<T>`, `list<T>`, `stack<T>`).

2. **Algoritmos genéricos**: Cuando implementas algoritmos que deben funcionar con múltiples tipos (ej: ordenamiento, búsqueda, operaciones matemáticas).

3. **Evitar duplicación de código**: Cuando tienes código idéntico que solo difiere en el tipo de dato utilizado.

4. **Políticas y estrategias**: Cuando implementas patrones de diseño como Strategy o Policy que deben funcionar con diferentes tipos.

5. **Metaprogramación**: Cuando necesitas realizar cálculos o transformaciones en tiempo de compilación.

**Ejemplo práctico**:
```cpp
template<class T>
class Pila {
private:
    vector<T> elementos;
public:
    void push(T elemento) { elementos.push_back(elemento); }
    T pop() { 
        T ultimo = elementos.back();
        elementos.pop_back();
        return ultimo;
    }
};

// Uso con diferentes tipos
Pila<int> pilaEnteros;
Pila<string> pilaStrings;
Pila<Persona> pilaPersonas;
```

#### Ventajas

1. **Reutilización de código**: Una sola implementación funciona con múltiples tipos.

2. **Type safety**: Los errores de tipo se detectan en tiempo de compilación, no en ejecución.

3. **Rendimiento**: No hay overhead en tiempo de ejecución, el compilador genera código específico para cada tipo.

4. **Flexibilidad**: Permite crear código genérico que se adapta a diferentes necesidades.

5. **Abstracción**: Permite trabajar con conceptos abstractos sin preocuparse por tipos específicos.

6. **Estándar de C++**: La STL (Standard Template Library) está basada en templates, proporcionando contenedores y algoritmos eficientes.

7. **Especialización**: Permite crear versiones especializadas para tipos específicos cuando es necesario.

#### Desventajas

1. **Complejidad**: Pueden ser difíciles de entender y mantener, especialmente para programadores principiantes.

2. **Mensajes de error**: Los errores de compilación con templates pueden generar mensajes muy largos y difíciles de interpretar.

3. **Tiempo de compilación**: Pueden aumentar significativamente el tiempo de compilación, especialmente con templates complejos.

4. **Separación de código**: No se pueden separar fácilmente la declaración (.h) de la implementación (.cpp) como con clases normales (aunque hay técnicas para hacerlo).

5. **Debugging**: Puede ser más difícil depurar código template debido a la generación de código en tiempo de compilación.

6. **Sobrecarga de código**: El compilador genera una versión del código para cada tipo usado, lo que puede aumentar el tamaño del ejecutable.

7. **Requisitos del tipo**: Los tipos usados con templates deben cumplir ciertos requisitos (ej: tener constructor por defecto, operadores específicos), lo que puede limitar su uso.

8. **Curva de aprendizaje**: Requiere entender conceptos avanzados de C++ como especialización, SFINAE, traits, etc.

#### Comparación con Alternativas

**Templates vs Herencia Polimórfica**:
- **Templates**: Mejor rendimiento, type safety en compilación, pero menos flexible en tiempo de ejecución.
- **Herencia**: Más flexible en tiempo de ejecución, pero con overhead de virtual functions y menos type safety.

**Templates vs Macros**:
- **Templates**: Type safe, respetan scope, mejor debugging.
- **Macros**: No type safe, pueden causar efectos secundarios, más difíciles de depurar.

#### Ejemplo de Ventaja: STL

La STL es un excelente ejemplo de la utilidad de templates:

```cpp
vector<int> numeros;           // Contenedor de enteros
vector<string> palabras;       // Contenedor de strings
vector<Persona> personas;      // Contenedor de objetos Persona

// Mismo algoritmo funciona con diferentes tipos
sort(numeros.begin(), numeros.end());
sort(palabras.begin(), palabras.end());
```

Sin templates, necesitarías implementar `VectorInt`, `VectorString`, `VectorPersona`, etc., duplicando código.

#### Conclusión

Las clases template son necesarias porque proporcionan una forma poderosa y eficiente de crear código genérico y reutilizable. Aunque tienen algunas desventajas en términos de complejidad y tiempo de compilación, sus ventajas en términos de reutilización, type safety y rendimiento las hacen esenciales en la programación moderna en C++. Son especialmente útiles para crear bibliotecas genéricas como la STL, donde una sola implementación debe funcionar con múltiples tipos de datos.

## Diseño del Sistema

### Clases Implementadas

1. **Respuesta**: Representa una respuesta a una pregunta
   - Tiene texto
   - Puede tener preguntas encadenadas (composición)
   - Operador `<<` implementado

2. **Pregunta**: Representa una pregunta de la encuesta
   - Tiene texto
   - Tiene respuestas (composición)
   - Operador `<<` implementado

3. **Encuesta**: Representa una encuesta completa
   - Tiene título
   - Tiene preguntas (composición)
   - Operador `<<` implementado

4. **Gestora**: Gestiona el sistema de encuestas
   - Lectura/escritura de archivos binarios (4 archivos)
   - Procedimiento para responder encuesta
   - Funciones STL:
     - `obtenerPreguntasConMasRespuestas()`: usa `max_element` de STL
     - `obtenerRespuestasConPreguntasEncadenadas()`: recorre todas las respuestas
   - Guardar en texto con operador `<<`

### Relaciones

- **Composición**: Encuesta tiene Preguntas
- **Composición**: Pregunta tiene Respuestas
- **Composición**: Respuesta tiene Preguntas encadenadas

### Funcionalidades Implementadas

- **Punto 1 (30pts)**: Diseño y guardar en archivos binarios (4 archivos)
- **Punto 2 (30pts)**: Procedimiento para responder encuesta con preguntas encadenadas
- **Punto 3 (20pts)**: Funciones STL implementadas
- **Punto 4 (20pts)**: Respuestas teóricas sobre templates en README.md
- **Libre**: Guardar en texto con operador `<<` implementado
