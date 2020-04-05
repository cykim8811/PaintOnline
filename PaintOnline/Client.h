#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <vector>

#include "tools.h"

using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;

class Client {
public:
	Client(char* IP, unsigned short PORT);
	virtual void tick(double dT) {};
	virtual int receive(char* data) { return -1; };
	void send(char* data);

	io_service ioservice;
	thread* t_run;
	tcp::endpoint* endpoint;
	tcp::socket* socket;
};
