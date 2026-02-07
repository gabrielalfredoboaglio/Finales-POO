# Sistema de Dependencias de Paquetes de Software

## Respuestas Teóricas

### Ejercicio 4 (22 puntos) - ¿Qué operador debería sobreescribir al tipo T para poder utilizar esta estructura?

Se debe sobreescribir el **operador `<` (menor que)** en el tipo T para poder utilizar la estructura `VectorOrdenado<T>`.

Esto es necesario porque la estructura mantiene los elementos ordenados y, al momento de insertar un nuevo elemento, necesita comparar con los elementos existentes para encontrar la posición correcta donde insertarlo. La comparación se realiza mediante el operador `<`, que determina si un elemento es menor que otro.

Por ejemplo, si queremos usar `VectorOrdenado<Paquete>`, la clase `Paquete` debería implementar:

```cpp
bool operator<(Paquete& otro) {
    return strcmp(this->codigo, otro.codigo) < 0;
}
```

De esta manera, el vector podrá ordenar los paquetes alfabéticamente por código. Sin este operador, la estructura no podría determinar el orden relativo entre dos elementos de tipo T.

---

### Ejercicio 5 (16 puntos) - ¿Cuándo es necesario utilizar composición y cómo ayuda a reutilizar código? El polimorfismo simplifica el diseño del código, ¿cómo? Justifique.

#### ¿Cuándo es necesario utilizar composición?

La composición es necesario utilizarla cuando una clase **"tiene"** o **"contiene"** a otra clase como parte de su estructura. Se aplica cuando existe una relación **"tiene-un"** (has-a) entre dos clases, en lugar de una relación **"es-un"** (is-a) que correspondería a herencia.

**Casos donde es necesaria:**

1. **Cuando una entidad contiene a otras**: Por ejemplo, en este sistema, un `ConjuntoPaquetes` **tiene** varios `Paquete`. El conjunto no **es** un paquete, sino que contiene paquetes.

2. **Cuando se quiere reutilizar funcionalidad sin herencia**: Si una clase necesita usar las capacidades de otra pero no tiene una relación jerárquica con ella.

3. **Cuando los componentes pueden existir independientemente**: Un `Paquete` puede existir sin pertenecer a ningún conjunto, y puede ser parte de múltiples conjuntos.

#### ¿Cómo ayuda la composición a reutilizar código?

La composición ayuda a reutilizar código porque permite que una clase **delegue responsabilidades** a las clases que contiene, sin necesidad de reimplementar la lógica. Por ejemplo:

- `ConjuntoPaquetes` reutiliza el método `obtenerTodasDependencias()` de `Paquete` para calcular todas las dependencias transitivas del conjunto, sin tener que reimplementar la lógica de recorrido recursivo.
- Si la lógica de dependencias cambia en `Paquete`, automáticamente se actualiza en `ConjuntoPaquetes` sin modificar su código.

Esto promueve el principio **DRY** (Don't Repeat Yourself) y permite construir clases complejas combinando clases más simples.

#### ¿Cómo el polimorfismo simplifica el diseño del código?

El polimorfismo simplifica el diseño del código permitiendo **tratar objetos de diferentes tipos de manera uniforme** a través de una interfaz común. Esto se logra mediante:

1. **Código genérico**: Se puede escribir código que funcione con la clase base y automáticamente funcione con cualquier clase derivada. Por ejemplo, si tuviéramos `PaqueteNormal` y `PaqueteCompuesto` heredando de `Paquete`, podríamos tratarlos a todos como `Paquete*` sin necesidad de verificar el tipo específico.

2. **Eliminación de condicionales**: Sin polimorfismo, tendríamos que usar `if-else` o `switch` para determinar el tipo del objeto y ejecutar el comportamiento correspondiente. Con polimorfismo, cada clase implementa su propia versión del método virtual, y el sistema elige automáticamente la implementación correcta en tiempo de ejecución (enlace dinámico).

3. **Extensibilidad**: Si se necesita agregar un nuevo tipo, basta con crear una nueva clase derivada que implemente los métodos virtuales, sin modificar el código existente que trabaja con la clase base. Esto cumple con el **Principio Abierto/Cerrado** (abierto para extensión, cerrado para modificación).

4. **Ejemplo práctico**: En lugar de:
   ```cpp
   if(paquete->getTipo() == "normal") {
       // hacer algo
   } else if(paquete->getTipo() == "compuesto") {
       // hacer otra cosa
   }
   ```
   Con polimorfismo simplemente:
   ```cpp
   paquete->ejecutar(); // Cada tipo sabe cómo ejecutar su lógica
   ```

En resumen, el polimorfismo **simplifica** el diseño al reducir la complejidad condicional, facilitar la extensión del sistema y permitir escribir código más limpio, mantenible y flexible.

---

## Diseño del Sistema

### Clases Implementadas

1. **Paquete**: Representa un paquete de software con código, nombre, versión y sus dependencias.
   - Relación con dependencias: **Agregación** (un paquete puede depender de varios paquetes compartidos)

2. **ConjuntoPaquetes** (Libre): Representa un conjunto de paquetes que permite instalar todos los paquetes dependientes.
   - Relación con paquetes: **Agregación** (un conjunto tiene varios paquetes compartidos)

3. **VectorOrdenado\<T\>**: Estructura template que representa un vector dinámico ordenado sin STL.

4. **Gestora**: Gestiona todos los paquetes, conjuntos, archivos y operaciones STL.

### Relaciones

- **Agregación**: Paquete tiene dependencias (vector\<Paquete*\>) - relación muchos a muchos
- **Agregación**: ConjuntoPaquetes tiene paquetes (vector\<Paquete*\>)
- **Composición**: Gestora gestiona paquetes y conjuntos
