#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Comandos del sistema
    gestora.mkdir("documentos");
    gestora.mkdir("imagenes");
    gestora.touch("archivo1.txt", 1024);
    gestora.touch("archivo2.txt", 2048);
    
    gestora.cd("documentos");
    gestora.touch("doc1.pdf", 5120);
    gestora.mkdir("subcarpeta");
    
    gestora.pwd();
    gestora.ls();
    gestora.lsp();
    
    gestora.cd("..");
    gestora.pwd();
    gestora.ls();

    return 0;
}
