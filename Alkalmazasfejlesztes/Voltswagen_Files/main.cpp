#include "StvApplication.h"
#include "Communication/CommunicationSerialPort.h"


int main(int argc, char *argv[])
{

    StvApplication app(argc, argv);
    return app.exec();
}
