#include <iostream>
#include <cstdlib>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

NetSocketPP::ServerFunctionArgs& serverMain(NetSocketPP::ServerFunctionArgs args, NetSocketPP::ServerSocket* sck) {
	bool init = false;
	string id = "";
	sck->recv(0);
	string msg;
	msg = sck->get();
	if(msg == "INIT") {
		init = true;
		sck->send("OK", 0);
		cout << "Connection initiated!" << endl;
	} else {
		sck->send("REJECT", 0);
		cout << "Rejected a connection!" << endl;
		return args;
	}
	while(init) {	
	sck->recv(0);
	string msg;
	msg = sck->get();
	if(msg[0] == 'I' && msg[1] == 'D') {
	for(int i = 3; i < msg.length(); i++) {
	id += msg[i];	
	}
	sck->send("OK", 0);
	cout << "User identified itself as: " << id << endl;
	} else if(msg == "CLOSE") {
	cout << "Closed a connection!" << endl;
	sck->send("OK", 0);
	init = false;	
	} else {
	cout << "Bad command received: " << msg << endl;
	sck->send("BADCOM", 0);	
	}
	}
	return args;
}

int main() {
try {
NetSocketPP::ServerSocket srv("localhost", "8111", "TCP");
NetSocketPP::ServerFunctionArgs outargs;
NetSocketPP::ServerFunctionArgs args;
srv.startServer(outargs, serverMain, args, "true", 0, 10);
return EXIT_SUCCESS;
} catch(NetSocketPP::NetworkException &exc) {
cerr << "Connection error: " << exc.what() << endl;	
return 2;
} catch(NetSocketPP::SocketException &exc) {
cerr << "NetSocket++ library error: " << exc.what() << endl;
return 1;
}
}
