#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

string strip_endl(string s) {
	string r = "";
for(int i = 0; i < s.length(); i++) {
if(s[i] != '\n' && s[i] != '\r') {
	r += s[i];
}
}
return r;
}

string int_to_string(int i) {
if(i == 0) {
return "0";	
} else if(i == 1) {
return "1";	
} else if(i == 2) {
return "2";	
} else if(i == 3) {
return "3";
} else if(i == 4) {
return "4";	
} else if(i == 5) {
return "5";
} else if(i == 6) {
return "6";
} else if(i == 7) {
return "7";	
} else if(i == 8) {
return "8";	
} else if(i == 9) {
return "9";	
}
int k = 1;
cout << "DEBUG: k: " << k << endl;
while(i/k != 0) {
k *= 10;
}
cout << "DEBUG: k: " << k << endl;
string s;
while(k > 1) {
k /= 10;
int p = i/k;
cout << "DEBUG: p: " << p << endl;
if(p == 0) {
s += "0";	
} else if(p == 1) {
s += "1";	
} else if(p == 2) {
s += "2";	
} else if(p == 3) {
s += "3";
} else if(p == 4) {
s += "4";	
} else if(p == 5) {
s += "5";
} else if(p == 6) {
s += "6";
} else if(p == 7) {
s += "7";	
} else if(p == 8) {
s += "8";	
} else if(p == 9) {
s += "9";	
}
i -= k*p;
}
}

int file_write(string filename, string msg) {
ofstream out(filename.c_str(), ios_base::app);
if(!out) {
	cerr << "Could not open log file!" << endl;
	return 1;
}
srand(time(NULL));
int st = rand()%5+1;
sleep(st);
time_t tt;
tt = time(&tt);
string stime = "";
stime += ctime(&tt);
out << strip_endl(stime) << ": " << msg << endl;
out.close();
return 0;
}

NetSocketPP::ServerFunctionArgs& serverMain(NetSocketPP::ServerFunctionArgs args, NetSocketPP::ServerSocket* sck) {
	std::string msg;
	sck->recv(0);
	msg = sck -> get();
	if(msg == "INIT CLIENT") {
		time_t tt;
		tt = time(&tt);
		string stime = "";
		stime += ctime(&tt);
		cout << strip_endl(stime) << ": Client connection received!" << endl;
		int fwret;
		fwret = file_write("SCServer.log", "Client connection received!");
		int k = 0;
		while(fwret != 0 && k < 50) {
		fwret = file_write("SCServer.log", "Client connection received!");
		k++;
		}
		if(k >= 50) {
		cerr << "Could not open SCServer.log for writing!" << endl;
		sck -> send("SERVER ERROR", 0);
		return args;
		}
		sck->send("COMMAND ACCEPT", 0);
		sck->recv(0);
		msg = sck -> get();
		if(msg[0] == 'I' && msg[1] == 'D') {
			string id = "";
			for(int i = 2; i < msg.length(); i++) {
				id += msg[i];
			}
		time_t tt;
		tt = time(&tt);
		string stime = "";
		stime += ctime(&tt);
		cout << strip_endl(stime) << ": Client identified as: " << id << "!" << endl;
		string str = "Client identified as: " + id + "!";
		fwret = file_write("SCServer.log", str);
		k = 0;
		while(fwret != 0 && k < 50) {
		fwret = file_write("SCServer.log", str);
		k++;
		}
		if(k >= 50) {
		cerr << "Could not open SCServer.log for writing!" << endl;
		sck -> send("SERVER ERROR", 0);
		return args;
		}
		string rmsg;
		rmsg = "*** " + id + " joined conversation! ***";
		fwret = file_write("SCConv.log", rmsg);
				k = 0;
				while(fwret != 0 && k < 50) {
					fwret = file_write("SCConv.log", rmsg);
					k++;
				}
				if(k >= 50) {
					cerr << "Could not open SCConv.log for writing!" << endl;
					sck -> send("SERVER ERROR", 0);
					return args;
				}
		sck -> send("COMMAND ACCEPT", 0);
		bool init = true;
		while(init) {
			sck->recv(0);
			msg = sck -> get();
			if(msg[0] == 'M' && msg[1] == 'S' && msg[2] == 'G') {
				string rmsg = "";
				rmsg += id;
				rmsg += ": ";
				for(int i = 3; i < msg.length(); i++) {
					rmsg += msg[i];
				}
				time_t tt;
				tt = time(&tt);
				string stime = "";
				stime += ctime(&tt);
			cout << strip_endl(stime) << ": " << id << "' s message received!" << endl;
				fwret = file_write("SCConv.log", rmsg);
				k = 0;
				while(fwret != 0 && k < 50) {
					fwret = file_write("SCConv.log", rmsg);
					k++;
				}
				if(k >= 50) {
					cerr << "Could not open SCConv.log for writing!" << endl;
					sck -> send("SERVER ERROR", 0);
					return args;
				}
				sck -> send("COMMAND ACCEPT", 0);
			} else if(msg == "CLOSE") {
				init = false;
				time_t tt;
		tt = time(&tt);
		string stime = "";
		stime += ctime(&tt);
					cout << strip_endl(stime) << ": " << id << " closed connection!" << endl;
					string rmsg = id + " closed connection!";
				fwret = file_write("SCServer.log", rmsg);
				k = 0;
				while(fwret != 0 && k < 50) {
					fwret = file_write("SCServer.log", rmsg);
					k++;
				}
				if(k >= 50) {
					cerr << "Could not open SCServer.log for writing!" << endl;
					sck -> send("SERVER ERROR", 0);
					return args;
				}
				rmsg = "*** " + id + " left conversation! ***";
		fwret = file_write("SCConv.log", rmsg);
				k = 0;
				while(fwret != 0 && k < 50) {
					fwret = file_write("SCConv.log", rmsg);
					k++;
				}
				if(k >= 50) {
					cerr << "Could not open SCConv.log for writing!" << endl;
					sck -> send("SERVER ERROR", 0);
					return args;
				}
				sck -> send("COMMAND ACCEPT", 0);
			} else {
			sck->send("COMMAND REJECT", 0);	
			}
		}
		} else {
			sck->send("COMMAND REJECT", 0);
		}
		return args;
	} else if(msg == "INIT VIEWER") {
		time_t tt;
		tt = time(&tt);
		string stime = "";
		stime += ctime(&tt);
		cout << strip_endl(stime) << ": Viewer connection received!" << endl;
		int fwret;
		fwret = file_write("SCServer.log", "Viewer connection received!");
		int k = 0;
		while(fwret != 0 && k < 50) {
		fwret = file_write("SCServer.log", "Viewer connection received!");
		k++;
		}
		if(k >= 50) {
		cerr << "Could not open SCServer.log for writing!" << endl;
		sck -> send("SERVER ERROR", 0);
		return args;
		}
		sck->send("COMMAND ACCEPT", 0);
		bool init = true;
		int firstLineToSend = 0;
		while(init) {
		ifstream in("SCConv.log");
		if(!in) {
			cerr << "Could not open conversation log!" << endl;
			sck -> send("SERVER ERROR", 0);
		}
		//cout << "DEBUG: Init..." << endl;
		vector<string> current_log;
		while(!in.eof()) {
			string line = "";
			char c;
			in.get(c);
			while(c != '\n') {
			if(in) {
			line += c;
			in.get(c);
			}	
			}
			if(in) {
			//cout << "DEBUG: Line: " << line << endl;
			if(line != "" && line != " " && line != "\n") {
			current_log.push_back(line);
			}
			}
		}
		in.close();
		int nextLine = current_log.size();
		sck->recv(0);
		msg = sck->get();
		if(msg == "LOGINIT") {
			firstLineToSend = nextLine-51;
			//cout << "DEBUG: nextLine: " << nextLine << endl;
			//cout << "DEBUG: firstLineToSend: " << firstLineToSend << endl;
			if(firstLineToSend < 0) {
			firstLineToSend = 0;	
			}
			//cout << "DEBUG: firstLineToSend: " << firstLineToSend << endl;
			int dataSend = nextLine-firstLineToSend;
			//cout << "DEBUG: dataSend: " << dataSend << endl;
			string cmd = "DATASEND " +  int_to_string(dataSend);
			sck->send(cmd, 0);
			for(int i = firstLineToSend; i < nextLine; i++) {
				sck->send(current_log[i]+"\n", 0);
				//cout << "DEBUG: send..." << endl;
				firstLineToSend++;
				sleep(1);
			}
		} else if(msg == "UPDATE") {
			//cout << "DEBUG: Update..." << endl;
			int dataSend = nextLine-firstLineToSend;
			//cout << "DEBUG: nextLine: " << nextLine << endl;
			//cout << "DEBUG: firstLineToSend: " << firstLineToSend << endl;
			//cout << "DEBUG: dataSend: " << dataSend << endl;
			if(dataSend < 0) {
			dataSend = 0;	
			}
			string cmd = "DATASEND " + int_to_string(dataSend);
			//cout << "DEBUG: cmd: " << cmd << endl;
			sck->send(cmd, 0);
			//cout << "DEBUG: send..." << endl;
			sleep(1);
			for(int i = firstLineToSend; i < nextLine; i++) {
				sck->send(current_log[i]+"\n", 0);
				//cout << "DEBUG: send..." << endl;
				firstLineToSend++;
				sleep(1);
			}
		} else if(msg == "CLOSE") {
		time_t tt;
		tt = time(&tt);
		stime = "";
		stime += ctime(&tt);
		cout << strip_endl(stime) << ": Viewer connection closed!" << endl;
		int fwret;
		fwret = file_write("SCServer.log", "Viewer connection closed!");
		int k = 0;
		while(fwret != 0 && k < 50) {
		fwret = file_write("SCServer.log", "Viewer connection closed!");
		k++;
		}
		if(k >= 50) {
		cerr << "Could not open SCServer.log for writing!" << endl;
		sck -> send("SERVER ERROR", 0);
		return args;
		}
		sck->send("COMMAND ACCEPT", 0);
		} else {
		sck->send("COMMAND REJECT", 0);	
		}
		}
		return args;
	} else {
		sck->send("COMMAND REJECT", 0);
	}
}

int main() {
cout << "Phitherek_' s SimpleCom v. 0.1 Server (C) 2013 by Phitherek_" << endl;
cout << "Powered by NetSocket++ v. 0.1 (C) 2012-2013 by Phitherek_" << endl;
string port;
cout << "Enter port: ";
cin >> port;
	try {
	NetSocketPP::ServerSocket srv("localhost", port, "TCP");
	NetSocketPP::ServerFunctionArgs inargs;
	NetSocketPP::ServerFunctionArgs outargs;
	time_t tt;
		tt = time(&tt);
		string stime = "";
		stime += ctime(&tt);
		cout << strip_endl(stime) << ": Starting server..." << endl;
		int fwret;
		fwret = file_write("SCServer.log", "Starting server...");
		int k = 0;
		while(fwret != 0 && k < 50) {
		fwret = file_write("SCServer.log", "Starting server...");
		k++;
		}
		if(k >= 50) {
		cerr << "Could not open SCServer.log for writing!" << endl;
		return EXIT_FAILURE;
		}
	srv.startServer(outargs, serverMain, inargs, true, 0, 50);
	return EXIT_SUCCESS;
	} catch(NetSocketPP::NetworkException &exc) {
cerr << "Connection error: " << exc.what() << endl;	
return 2;
} catch(NetSocketPP::SocketException &exc) {
cerr << "NetSocket++ library error: " << exc.what() << endl;
return 1;
}
}
