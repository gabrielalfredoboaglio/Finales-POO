#ifndef VENTA_H
#define VENTA_H



class Venta {
private:
    int nro_cliente;
    int cantidad;
    double montoTotal;

public:
    Venta();
    Venta(int nro_cli, int cant, double monto);

    int getNroCliente();
    int getCantidad();
    double getMontoTotal();

    void setNroCliente(int nro);
    void setCantidad(int cant);
    void setMontoTotal(double monto);


};
#endif
