#include <iostream>
#include <cstdlib>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main(int argc, char** argv) {
string host = "";
if(argc > 1) {
	host = argv[1];
} else {
	host = "localhost";
}
try {
NetSocketPP::ClientSocket cli(host, "8111", "TCP");
cli.send("INIT", 0);
cli.recv(0);
if(cli.get() == "OK") {
	std::string id = "";
	cout << "Identify yourself: " << endl;
	cin >> id;
	std::string msg;
	msg += "ID ";
	msg += id;
	cli.send(msg, 0);
	cli.recv(0);
	if(cli.get() == "OK") {
	cout << "Identification successfully completed! Closing connection..." << endl;
	cli.send("CLOSE", 0);
	cli.recv(0);
	if(cli.get() == "OK") {
	cout << "Connection closed! All OK!" << endl;	
	} else if(cli.get() == "BADCOM") {
	cerr << "Server responded with a bad command error!" << endl;
	return EXIT_FAILURE;	
	}
	} else if(cli.get() == "BADCOM") {
	cerr << "Server responded with a bad command error!" << endl;
	return EXIT_FAILURE;	
	}
} else {
	cerr << "Connection to the server refused!" << endl;
	return EXIT_FAILURE;	
}
return EXIT_SUCCESS;
} catch(NetSocketPP::NetworkException &exc) {
cerr << "Connection error: " << exc.what() << endl;	
return 2;
} catch(NetSocketPP::SocketException &exc) {
cerr << "NetSocket++ library error: " << exc.what() << endl;
return 1;
}
}
