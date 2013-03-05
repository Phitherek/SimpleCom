#include <iostream>
#include <cstdlib>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main() {
cout << "Phitherek_' s SimpleCom v. 0.1 Client (C) 2013 by Phitherek_" << endl;
cout << "Powered by NetSocket++ v. 0.1 (C) 2012-2013 by Phitherek_" << endl;
string host;
cout << "Connect to server: ";
cin >> host;
string port;
cout << "Enter port: ";
cin >> port;
try {
NetSocketPP::ClientSocket cli(host, port, "TCP");
string msg;
cout << "Opening client connection..." << endl;
cli.send("INIT CLIENT", 0);
cli.recv(0);
msg = cli.get();
if(msg == "COMMAND ACCEPT") {
cin.ignore();
cout << "Connection successful!" << endl << "Enter your ID: ";
string id = "";
char c;
cin.get(c);
while(c != '\n') {
id += c;
cin.get(c);
}
string cmd = "";
cmd += "ID ";
cmd += id;
//cout << "DEBUG: CMD: " << cmd << endl;
cli.send(cmd, 0);
cli.recv(0);
msg = cli.get();
if(msg == "COMMAND ACCEPT") {
cout << "ID transaction complete!" << endl;
bool init = true;
while(init) {
cout << "Enter a message or /exit to exit: ";
string tosend = "";
char x;
cin.get(x);
while(x != '\n') {
tosend += x;
cin.get(x);
}
//cout << "DEBUG: tosend: " << tosend << endl;
if(tosend == "/exit") {
	init = false;
	cout << "Closing connection..." << endl;
	cli.send("CLOSE", 0);
	cli.recv(0);
	msg = cli.get();
	if(msg == "COMMAND ACCEPT") {
cout << "Connection closed!" << endl;
return EXIT_SUCCESS;
} else if(msg == "SERVER ERROR") {
	cerr << "Server error occured!" << endl;
	return EXIT_FAILURE;
} else if(msg == "COMMAND REJECT") {
	cerr << "Command was rejected!" << endl;
	return EXIT_FAILURE;
} else {
	cerr << "An error has occured!" << endl;
	return EXIT_FAILURE;
}
} else {
cmd = "";
cmd += "MSG ";
cmd += tosend;
cli.send(cmd, 0);
cli.recv(0);
msg = cli.get();
if(msg == "COMMAND ACCEPT") {
cout << "Message sent successfully!" << endl;	
} else if(msg == "SERVER ERROR") {
	cerr << "Server error occured!" << endl;
	return EXIT_FAILURE;
} else if(msg == "COMMAND REJECT") {
	cerr << "Command was rejected!" << endl;
	return EXIT_FAILURE;
} else {
	cerr << "An error has occured!" << endl;
	return EXIT_FAILURE;
}
}
}
} else if(msg == "SERVER ERROR") {
	cerr << "Server error occured!" << endl;
	return EXIT_FAILURE;
} else if(msg == "COMMAND REJECT") {
	cerr << "Command was rejected!" << endl;
	return EXIT_FAILURE;
} else {
	cerr << "An error has occured!" << endl;
	return EXIT_FAILURE;
}
} else if(msg == "SERVER ERROR") {
	cerr << "Server error occured!" << endl;
	return EXIT_FAILURE;
} else if(msg == "COMMAND REJECT") {
	cerr << "Command was rejected!" << endl;
	return EXIT_FAILURE;
} else {
	cerr << "An error has occured!" << endl;
	return EXIT_FAILURE;
}
} catch(NetSocketPP::NetworkException &exc) {
cerr << "Connection error: " << exc.what() << endl;	
return 2;
} catch(NetSocketPP::SocketException &exc) {
cerr << "NetSocket++ library error: " << exc.what() << endl;
return 1;
}
}
