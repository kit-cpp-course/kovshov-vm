#include <iostream>
#include "parserJSON.h"
#include "parserXML.h"

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << "\n";
    }
    /*
     * Объекты парсеров
     */
    parser *XML_P = new parserXML;
    parser *JSON_P = new parserJSON;
    return 0;
}



/*
 string input = "{\"menu\": {\n"
                   "  \"id\": \"file\",\n"
                   "  \"value\": \"File\",\n"
                   "  \"popup\": {\n"
                   "    \"menuitem\": [\n"
                   "      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},\n"
                   "      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},\n"
                   "      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}\n"
                   "    ]\n"
                   "  }\n"
                   "}}";


    string inputJSON = R"({"name":"Valery","age":18})";
    string inputXML = R"(<name>Darya<\name><age>300<\age>)";

    string XML = "<person>\n"
                 "  <firstName>Ivan</firstName>\n"
                 "  <lastName>Ivanov</lastName>\n"
                 "  <address>\n"
                 "    <streetAddress>Moscow sh., 101, kv.101</streetAddress>\n"
                 "    <city>Leningrad</city>\n"
                 "    <postalCode>101101</postalCode>\n"
                 "  </address>\n"
                 "  <phoneNumbers>\n"
                 "    <phoneNumber>812 123-1234</phoneNumber>\n"
                 "    <phoneNumber>916 123-4567</phoneNumber>\n"
                 "  </phoneNumbers>\n"
                 "</person>";

    cout << JSON_P->parseFromObject(XML_P->parseToObject(XML));

    cout << XML_P->parseFromObject(XML_P->parseToObject(XML));

    //cout << JSON_P->parseFromObject(XML_P->parseToObject(inputXML));

 */