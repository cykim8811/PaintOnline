#include "Server.h"

void runner_ftn(Server* self) {
	bool running = true;
	while (running) {
		char buf[128] = { 0 };
		boost::system::error_code error;
		for (int i = 0; i < self->clients.size(); i++) {
			self->clients[i]->read_some(boost::asio::buffer(buf), error);
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
		}
		self->tick(0.01);
		this_thread::sleep_for(0.01s);
	}
}

void accept_client(Server* self) {
	while (true) {
		tcp::socket* socket = new tcp::socket(self->ioservice);
		self->acceptor->accept(*socket);
		self->clients.push_back(socket);
		// new thread(run_client, socket);
	}
}

Server::Server(unsigned short PORT) {
	endpoint = new tcp::endpoint(tcp::v4(), PORT);
	acceptor = new tcp::acceptor(ioservice, endpoint);
	t_run = new thread(runner_ftn, this);
	t_accept = new thread(runner_ftn, this);
}


void Server::send(char* data) {

}