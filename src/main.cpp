#include <windows.h>
#include "sistema.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Sistema sistema;
    sistema.Menu();

    return 0;
}
