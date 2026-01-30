int main() {
    Gestora gestor;

    // Crear tarea normal
    normal* t1 = new Normal();
    t1->setDescripcion("Reunión");
    t1->setFecha("20260130");
    t1->setHora("100000");
    t1->setDuracion(60);

    // Crear tarea compuesta
    MuchaTarea* proyecto = new MuchaTarea();
    proyecto->setDescripcion("Proyecto Final");
    proyecto->setFecha("20260130");
    proyecto->setHora("140000");
    proyecto->setDuracion(300);

    // Agregar subtareas al proyecto
    Normal* sub1 = new Normal();
    sub1->setDescripcion("Fase 1");
    proyecto->agregarSubtarea(sub1);

    Normal* sub2 = new Normal();
    sub2->setDescripcion("Fase 2");
    proyecto->agregarSubtarea(sub2);

    // Agregar tareas a la gestora
    gestor.add(t1);       // Tarea normal
    gestor.add(proyecto); // Tarea compuesta

    // GUARDAR EN ARCHIVO
    gestor.guardar();  // ← AQUÍ EMPIEZA EL FLUJO DE GUARDADO

    return 0;
}
