#include <iostream>
#include <string>
#include "../tinyxml/tinyxml.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: .exe <filePath>" << endl;
        return 0;
    }

    TiXmlDocument doc ( argv[1] );
    if (!doc.LoadFile()) {
        cerr << "Error: cannot read xml" << endl;
        return 0;
    }

    TiXmlElement* root = doc.FirstChildElement("root");

    printf("%s\n", root->Value());

    return 0;
}

