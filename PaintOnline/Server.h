#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <vector>

#include "tools.h"

using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;

class Server {
public:
	Server(unsigned short PORT);
	virtual void tick(double dT) {};
	virtual int receive(char* data) { return -1; };
	void send(tcp::socket* socket, char* data);

	io_service ioservice;
	thread* t_run;
	thread* t_accept;
	tcp::endpoint* endpoint;
	tcp::acceptor* acceptor;
	vector<tcp::socket*> clients;
};


