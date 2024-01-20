// serverM.h
#ifndef SERVERM_H
#define SERVERM_H

#include <iostream>
#include <string>
#include <unistd.h>


int MainServer_UDPClientSocket;
int MainServer_TCPClientSocket;
void start_mainserver();

std::string receiveClientReq();
void sendResult(int ans);

int serverType(char req[]);
void ReqToBackend(int servertype, char req[]);

void end_mainserver();

#endif // SERVERM_H
