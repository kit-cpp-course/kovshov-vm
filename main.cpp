#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

using namespace std;
using namespace boost::property_tree;

int main(int argc, char *argv[]) {
	
	cout << argc << endl;

	for (int i = 0; i < argc; i++)
		cout << argv[i] << endl;

	switch (argc)
	{
		case 2 :
		{
			string input = argv[1];
			cout << "Vvedeno dve peremenie\n";
			if (input.substr(input.length() - 3, 3) == "xml") {
				cout << "Input xml\n";
				ptree pt;
				read_xml(input, pt);
				try
				{
					write_json(cout, pt);
				}
				catch (const std::exception&)
				{
					cout << "Xml parsing exception\n";
				}
			}
			else if (input.substr(input.length() - 4, 4) == "json")
			{
				cout << "Input json\n";
				ptree pt;
				read_json(input, pt);
				try
				{
					write_xml(cout, pt);
				}
				catch (const std::exception&)
				{
					cout << "Json parsing exception\n";
				}
			}
			else
			{
				cout << "Input exception. Plece write path file to convert\n";
			}
			break;
		}
		case 3 :
		{
			string input = argv[1];
			string output = argv[2];
			cout << "Vvedeno tri peremenie\n";
			if (input.substr(input.length() - 3, 3) == "xml") {
				cout << "Input xml + Output\n";
				ptree pt;
				read_xml(input, pt);
				try
				{
					write_json(output, pt);
				}
				catch (const std::exception&)
				{
					cout << "Xml parsing exception\n";
				}
			}
			else if (input.substr(input.length() - 4, 4) == "json")
			{
				cout << "Input json + Output\n";
				ptree pt;
				read_json(input, pt);
				try
				{
					write_xml(output, pt);
				}
				catch (const std::exception&)
				{
					cout << "Json parsing exception\n";
				}
			}
			else
			{
				cout << "Input exception. Plece write path file to convert.\n";
			}
			break; 
		}
		default: {
			cout << "Input exception. Plece write path file to convert.\n";
		}		
	}
	return 0;
}