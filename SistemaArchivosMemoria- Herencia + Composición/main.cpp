#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    gestora.mkdir("documentos");
    gestora.mkdir("imagenes");
    gestora.touch("archivo1.txt", 1024);   // Libre: peso como parámetro
    gestora.touch("archivo2.txt", 2048);   // Libre: peso como parámetro
    
    gestora.cd("documentos");
    gestora.touch("doc1.pdf", 5120);   // Libre: peso como parámetro
    gestora.mkdir("subcarpeta");
    
    gestora.pwd();
    gestora.ls();
    gestora.lsp();
    
    gestora.cd("..");
    gestora.pwd();
    gestora.ls();

    return 0;
}
