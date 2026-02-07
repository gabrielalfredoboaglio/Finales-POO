# GreenGoldSoft - Sistema de Gestión de Cursos

## Respuestas Teóricas

### (15 puntos) Explique porque son necesarias las clases abstractas. ¿Cuándo las utilizaría? ¿Cuáles son sus ventajas y desventajas?

#### ¿Por qué son necesarias las clases abstractas?

Las clases abstractas son necesarias porque permiten definir una interfaz común para un conjunto de clases relacionadas, estableciendo un contrato que todas las clases derivadas deben cumplir. Esto garantiza que todas las subclases implementen los métodos esenciales definidos en la clase base, proporcionando una estructura consistente y predecible en el diseño orientado a objetos.

#### ¿Cuándo las utilizaría?

Las clases abstractas se utilizan cuando:

1. **Hay un concepto común pero con implementaciones diferentes**: Cuando varias clases comparten características similares pero tienen comportamientos específicos que deben implementarse de manera diferente. Por ejemplo, una clase `Animal` abstracta con métodos `hacerSonido()` y `mover()`, donde cada animal (Perro, Gato, Pájaro) tiene su propia implementación.

2. **Se necesita garantizar la implementación de métodos**: Cuando queremos asegurar que todas las clases derivadas implementen ciertos métodos críticos para el funcionamiento del sistema.

3. **Diseño de frameworks y bibliotecas**: Cuando se crea una estructura base que otros desarrolladores deben extender, proporcionando una plantilla clara de lo que se espera.

4. **Polimorfismo puro**: Cuando se necesita trabajar con objetos de diferentes tipos a través de una interfaz común, sin conocer el tipo específico en tiempo de compilación.

#### Ventajas

1. **Consistencia**: Garantiza que todas las clases derivadas implementen los métodos necesarios, manteniendo una interfaz uniforme.

2. **Flexibilidad**: Permite agregar nuevas clases derivadas sin modificar el código existente que usa la clase base (Principio Abierto/Cerrado).

3. **Polimorfismo**: Facilita el uso de polimorfismo, permitiendo tratar objetos de diferentes tipos de manera uniforme a través de punteros o referencias a la clase base.

4. **Documentación**: Sirve como documentación del diseño, mostrando claramente qué métodos deben implementarse.

5. **Reutilización de código**: Permite compartir código común en la clase base mientras se personaliza el comportamiento específico en las derivadas.

#### Desventajas

1. **Complejidad**: Aumenta la complejidad del diseño, especialmente para proyectos pequeños donde podría ser innecesario.

2. **Rigidez**: Una vez definida la interfaz abstracta, es difícil modificarla sin afectar todas las clases derivadas.

3. **Herencia múltiple limitada**: En C++, la herencia múltiple con clases abstractas puede volverse compleja y propensa a errores.

4. **Sobrecarga de diseño**: Puede llevar a un sobre-diseño si se usa innecesariamente, complicando el código sin beneficios reales.

5. **Curva de aprendizaje**: Requiere un entendimiento más profundo de conceptos de POO, lo que puede dificultar el mantenimiento por desarrolladores menos experimentados.

#### Relación con el polimorfismo

Las clases abstractas y el polimorfismo están íntimamente relacionados:

1. **Habilitan el polimorfismo**: Las clases abstractas permiten que objetos de diferentes clases derivadas sean tratados de manera uniforme a través de punteros o referencias a la clase base.

2. **Enlace dinámico (Dynamic Binding)**: Cuando se llama a un método virtual de una clase abstracta, el sistema determina en tiempo de ejecución qué implementación específica debe ejecutarse, basándose en el tipo real del objeto.

3. **Interfaz común**: Proporcionan una interfaz común que permite escribir código genérico que funciona con cualquier clase derivada, sin conocer el tipo específico.

4. **Ejemplo práctico**: 
   ```cpp
   // Clase abstracta
   class Animal {
   public:
       virtual void hacerSonido() = 0; // Método puro virtual
   };
   
   // Polimorfismo en acción
   Animal* animales[] = {new Perro(), new Gato(), new Pajaro()};
   for(Animal* a : animales) {
       a->hacerSonido(); // Cada uno hace su sonido específico
   }
   ```

En resumen, las clases abstractas son la base que permite el polimorfismo, proporcionando la estructura necesaria para que diferentes objetos respondan de manera específica a las mismas llamadas de métodos.

## Diseño del Sistema

### Clases Implementadas

1. **Curso**: Representa un curso normal con código, título, tiempo en horas y correlativas.
   - Relación con correlativas: **Agregación** (un curso puede tener varios cursos como correlativas)

2. **CursoCompuesto**: Hereda de Curso y representa un curso compuesto por otros cursos.
   - Relación con cursos contenidos: **Agregación** (un curso compuesto tiene varios cursos)
   - Herencia: **Herencia** de Curso

3. **Gestora**: Gestiona todos los cursos, archivos y operaciones STL.

### Relaciones

- **Agregación**: Curso tiene correlativas (vector<Curso*>)
- **Agregación**: CursoCompuesto tiene cursos (vector<Curso*>)
- **Herencia**: CursoCompuesto hereda de Curso
- **Polimorfismo**: Uso de getTipo() y dynamic_cast para diferenciar tipos
