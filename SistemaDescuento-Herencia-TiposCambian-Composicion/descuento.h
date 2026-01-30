#ifndef DESCUENTO_H
#define DESCUENTO_H

// ESTRATEGIA BASE - Define la interfaz para calcular descuentos
class Descuento {
public:

     ~Descuento() {}

    // Método virtual puro que cada estrategia concreta implementará
    virtual double calcularDescuento(int cantTotal, double montoTotal) const = 0;

    // Retorna el tipo de descuento ('A', 'B', 'C')
    virtual char getTipo() const = 0;
};

#endif
