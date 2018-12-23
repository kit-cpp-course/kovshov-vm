#include <iostream>
#include "jsonSimple.h"

int main() {

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

    JSON json(input);

    cout << json.toXML() << endl;

    return 0;
}