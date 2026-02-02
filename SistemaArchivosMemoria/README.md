# Sistema de Archivos en Memoria

## Respuestas Teóricas

### Indique las diferencias entre archivo binario y texto

#### Archivo de Texto

1. **Formato**: Contiene caracteres legibles por humanos, codificados según estándares como ASCII o UTF-8.

2. **Lectura**: Puede ser leído directamente con un editor de texto común (notepad, vim, etc.).

3. **Representación**: Cada byte representa un carácter o parte de un carácter (en codificaciones multibyte).

4. **Tamaño**: Generalmente más grande porque almacena datos en formato legible (ej: el número 12345 ocupa 5 bytes como texto, pero solo 4 bytes como entero binario).

5. **Portabilidad**: Depende de la codificación de caracteres, puede tener problemas entre diferentes sistemas operativos.

6. **Uso**: Ideal para configuración, logs, documentos, código fuente, datos que necesitan ser editados manualmente.

7. **Ejemplo**: Un archivo `.txt` con el contenido "Hola Mundo" almacena cada carácter como su código ASCII.

#### Archivo Binario

1. **Formato**: Contiene datos en su representación binaria directa, tal como se almacenan en memoria.

2. **Lectura**: No es legible directamente por humanos, requiere programas especializados para interpretarlo.

3. **Representación**: Los bytes representan valores directamente (enteros, flotantes, estructuras, etc.) sin conversión a texto.

4. **Tamaño**: Generalmente más compacto porque almacena datos en su formato nativo (ej: un entero de 4 bytes siempre ocupa 4 bytes).

5. **Portabilidad**: Puede tener problemas de endianness (orden de bytes) entre diferentes arquitecturas.

6. **Uso**: Ideal para datos estructurados, imágenes, audio, video, bases de datos, serialización de objetos.

7. **Ejemplo**: Un archivo `.dat` que almacena un entero 12345 lo guarda como los 4 bytes: `00 00 30 39` (en little-endian).

#### Diferencias Clave

| Aspecto | Archivo de Texto | Archivo Binario |
|---------|------------------|-----------------|
| **Legibilidad** | Legible por humanos | No legible directamente |
| **Tamaño** | Generalmente más grande | Generalmente más compacto |
| **Velocidad** | Más lento (conversión texto↔número) | Más rápido (lectura/escritura directa) |
| **Precisión** | Puede perder precisión en números decimales | Mantiene precisión exacta |
| **Edición** | Fácil de editar manualmente | Requiere herramientas especializadas |
| **Estructura** | Secuencial, línea por línea | Puede tener estructura compleja |
| **Ejemplo** | `archivo.txt`: "123.45" | `archivo.dat`: bytes `42 F6 E6 66` |

#### Ejemplo Práctico en C++

```cpp
// Archivo de texto
ofstream texto("datos.txt");
texto << 12345 << endl;  // Escribe "12345" como texto (5 bytes)

// Archivo binario
ofstream binario("datos.dat", ios::binary);
int valor = 12345;
binario.write((char*)&valor, sizeof(int));  // Escribe 4 bytes directamente
```

### ¿La herencia genera acoplamiento? Justifique

**Sí, la herencia genera acoplamiento**, y es uno de los tipos de acoplamiento más fuertes en programación orientada a objetos.

#### ¿Qué es el acoplamiento?

El acoplamiento es el grado de interdependencia entre módulos o clases. Un acoplamiento alto significa que las clases están muy relacionadas y los cambios en una afectan a otras.

#### ¿Por qué la herencia genera acoplamiento?

1. **Dependencia estructural**: La clase derivada depende directamente de la estructura interna de la clase base. Cualquier cambio en la clase base puede afectar a todas las clases derivadas.

2. **Acceso a miembros protegidos**: Las clases derivadas tienen acceso a los miembros `protected` de la clase base, creando una dependencia directa con la implementación interna.

3. **Cambios en cascada**: Modificar la clase base puede requerir modificar todas las clases derivadas, especialmente si se cambian métodos virtuales o la interfaz pública.

4. **Acoplamiento de implementación**: La clase derivada conoce no solo la interfaz pública, sino también detalles de implementación de la clase base.

#### Ejemplo de Acoplamiento por Herencia

```cpp
class Base {
protected:
    int valor;  // La clase derivada depende de este campo
public:
    virtual void metodo() { /* implementación */ }
};

class Derivada : public Base {
public:
    void metodo() override {
        valor++;  // Acoplamiento: depende de la estructura de Base
    }
};
```

Si cambiamos `valor` en `Base`, `Derivada` se ve afectada.

#### Comparación con Otras Formas de Acoplamiento

1. **Composición vs Herencia**:
   - **Composición**: Acoplamiento más débil, solo depende de la interfaz pública
   - **Herencia**: Acoplamiento más fuerte, depende de estructura e implementación

2. **Interfaces vs Herencia**:
   - **Interfaces**: Acoplamiento débil, solo contrato
   - **Herencia concreta**: Acoplamiento fuerte, implementación compartida

#### Ventajas y Desventajas del Acoplamiento por Herencia

**Ventajas**:
- Permite reutilización de código
- Facilita el polimorfismo
- Establece relaciones "es-un" claras

**Desventajas**:
- Alto acoplamiento dificulta el mantenimiento
- Cambios en la clase base afectan a todas las derivadas
- Dificulta el testing unitario
- Viola el principio de inversión de dependencias (DIP) si no se usa correctamente

#### Cómo Reducir el Acoplamiento

1. **Favor composición sobre herencia**: Usar composición cuando sea posible.
2. **Interfaces abstractas**: Usar clases abstractas o interfaces en lugar de herencia concreta.
3. **Principio de sustitución de Liskov**: Asegurar que las clases derivadas puedan sustituir a la base sin romper el código.
4. **Encapsulación**: Limitar el acceso a miembros protegidos.

#### Conclusión

La herencia genera acoplamiento porque crea una dependencia estructural y de implementación entre clases. Aunque es útil para modelar relaciones "es-un" y permitir polimorfismo, debe usarse con cuidado. El acoplamiento no es necesariamente malo, pero debe ser consciente y controlado. En muchos casos, la composición ofrece una alternativa con menor acoplamiento.

## Diseño del Sistema

### Clases Implementadas

1. **Nodo** (Clase Abstracta): Clase base para Archivo y Carpeta
   - Path y nombre
   - Métodos virtuales puros: `getTipo()` y `obtenerPeso()`

2. **Archivo**: Hereda de Nodo
   - Tiene peso (ejercicio libre)
   - `obtenerPeso()` retorna su peso

3. **Carpeta**: Hereda de Nodo
   - Contiene vector de Nodos (polimorfismo)
   - `obtenerPeso()` suma el peso de todos sus elementos (ejercicio libre)
   - Método `ordenarPorNombre()` para el comando `ls`

4. **Gestora**: Gestiona el sistema de archivos
   - Comandos: `mkdir`, `touch`, `cd`, `ls`, `lsp`, `pwd`
   - Mantiene referencia a root y carpeta actual

### Relaciones

- **Herencia**: Archivo y Carpeta heredan de Nodo (clase abstracta)
- **Polimorfismo**: Carpeta contiene vector<Nodo*> para almacenar archivos y carpetas
- **Composición**: Carpeta contiene Nodos (aunque técnicamente es agregación ya que no los destruye)

### Comandos Implementados

- **mkdir**: Crea una carpeta en la carpeta actual
- **touch**: Crea un archivo con peso en la carpeta actual
- **cd**: Cambia a otra carpeta (soporta ".." y "/")
- **ls**: Lista elementos ordenados por nombre
- **lsp**: Lista elementos y guarda en "display.txt"
- **pwd**: Muestra el path actual

### Ejercicio Libre

- Los archivos tienen peso (se pasa al crear con `touch`)
- Las carpetas calculan su peso sumando el peso de todos sus elementos recursivamente
