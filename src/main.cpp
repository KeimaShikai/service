// Костылёк для ревью
#include "CMain.h"

int main()
{
    CMain cMain;

    while(1)
    {
        cMain.initialisation();
        cMain.communication();
        cMain.disconnection();
    }
    return 0;
}
