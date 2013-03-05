#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

static bool bexit = false;

void sa_exit(int i) {
bexit = true;	
}

int main() {
cout << "Phitherek_' s SimpleCom v. 0.1 Viewer Client (C) 2013 by Phitherek_" << endl;
cout << "Powered by NetSocket++ v. 0.1 (C) 2012-2013 by Phitherek_" << endl;
cout << "Press Ctrl-C to exit" << endl;
string host;
cout << "Connect to server: ";
cin >> host;
string port;
cout << "Enter port: ";
cin >> port;
try {
NetSocketPP::ClientSocket cli(host, port, "TCP");
string msg;
cout << "Opening viewer connection..." << endl;
cli.send("INIT VIEWER", 0);
cli.recv(0);
msg = cli.get();
if(msg == "COMMAND ACCEPT") {
	cout << "Connection successfully opened! Sending start log request..." << endl;
	cli.send("LOGINIT", 0);
	cli.recv(0);
	msg = cli.get();
	//cout << "DEBUG: msg: " << msg << endl;
	if(msg[0] == 'D' && msg[1] == 'A' && msg[2] == 'T' && msg[3] == 'A' && msg[4] == 'S' && msg[5] == 'E' && msg[6] == 'N' && msg[7] == 'D') {
		string datalength = "";
		for(int i = 9; i < msg.length(); i++) {
			datalength += msg[i];
		}
		int idl;
		idl = atoi(datalength.c_str());
		//cout << "DEBUG: idl: " << idl << endl;
		if(idl == 0) {
		cout << "No data sent!" << endl;	
		} else {
		for(int i = 0; i < idl; i++) {
		//cout << "DEBUG: recv..." << endl;
		cli.recv(0);
		cout << cli.get();
		}
		}
		struct sigaction sa;
		sa.sa_handler=sa_exit;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
		//cout << "DEBUG: Before while..." << endl;
		while(!bexit) {
		//cout << "DEBUG: After while..." << endl;
		sleep(5);
		cli.send("UPDATE", 0);
		//cout << "DEBUG: Update sent!" << endl;
		cli.recv(0);
		msg = cli.get();
		// cout << "DEBUG: msg: " << msg << endl;
		while(msg == "" || msg == " " || msg == "\n") {
		cli.recv(0);
		msg = cli.get();
		}
		if(msg[0] == 'D' && msg[1] == 'A' && msg[2] == 'T' && msg[3] == 'A' && msg[4] == 'S' && msg[5] == 'E' && msg[6] == 'N' && msg[7] == 'D') {
		string datalength = "";
		for(int i = 9; i < msg.length(); i++) {
			datalength += msg[i];
		}
		int idl;
		idl = atoi(datalength.c_str());
		if(idl != 0) {
		for(int i = 0; i < idl; i++) {
		cli.recv(0);
		cout << cli.get();
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
		}
		cout << "Exiting and closing connection..." << endl;
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
