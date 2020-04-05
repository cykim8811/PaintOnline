#include "Client.h"

void runner_ftn(Client* self) {
	bool running = true;
	while (running) {
		char buf[128] = { 0 };
		boost::system::error_code error;
		self->socket->read_some(boost::asio::buffer(buf), error);
		if (error) {
			if (error == boost::asio::error::eof) {
				cout << "Disconnected" << endl;
				return;
			}
			else {
				cout << "Error " << error.value() << ":" << error.message() << endl;
				return;
			}
		}

		vector<string> splitted = split(buf, '\n');
		for (int i = 0; i < splitted.size(); i++) {
			int rec = self->receive(&splitted[i][0]);
			if (rec < 0) {
				running = false;
				break;
			}
		}
		self->tick(0.01);
		this_thread::sleep_for(0.01s);
	}
}

Client::Client(char* IP, unsigned short PORT) {
	endpoint = new tcp::endpoint(boost::asio::ip::address::from_string(IP), PORT);
	socket = new tcp::socket(ioservice);
	boost::system::error_code c_error;

	socket->connect(*endpoint, c_error);
	if (c_error) {
		if (c_error == boost::asio::error::eof) {
			cout << "Disconnected" << endl;
		}
		else {
			cout << "Error " << c_error.value() << ":" << c_error.message() << endl;
			exit(-1);
		}
	}
	t_run = new thread(runner_ftn, this);
}

void Client::send(char* data) {
	char dt[128];
	strcpy(dt, data);
	strcat(dt, "!");
	boost::system::error_code r_error;
	int len_r_buf = strnlen_s(dt, 128 - 1);
	socket->write_some(boost::asio::buffer(dt, len_r_buf), r_error);
}