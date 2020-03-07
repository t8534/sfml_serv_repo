//============================================================================
// Name        : sfml_serv.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// Time
// https://www.sfml-dev.org/tutorials/2.5/system-time.php
//
// Probably good code for chat.
// https://codereview.stackexchange.com/questions/160807/sfml-based-chat-in-c
//
// https://www.sfml-dev.org/tutorials/2.5/network-socket.php
//
// Look why this example is not working:
// https://www.gamedev.net/forums/topic/622478-sfml-network-examples/
//
// Example
// https://github.com/SFML/SFML/blob/master/examples/sockets/TCP.cpp
//
// https://en.sfml-dev.org/forums/index.php?topic=21565.0
//
// Basic chat example
// https://github.com/SFML/SFML/wiki/Source:-Network-Chat-Example
//
// https://www.sfml-dev.org/tutorials/1.6/network-sockets.php
//
// https://www.sfml-dev.org/tutorials/2.5/network-packet.php
//

// todo:
//
// 1.
// Take basic chat example as a start point:
// https://github.com/SFML/SFML/wiki/Source:-Network-Chat-Example
// then, after analyze add something from
// https://codereview.stackexchange.com/questions/160807/sfml-based-chat-in-c
//


// Then, you can wait for connections on this port.
//
//sf::IPAddress ClientAddress;
//sf::SocketTCP Client;
//if (Listener.Accept(Client, &ClientAddress) != sf::Socket::Done)
//{
//    // Error...
//}
//
// The Accept function will wait until an incoming connection arrives, and return a new socket
// that will be used to exchange data with the connected computer. If you pass a sf::IPAddress
// to the function, it will be filled with the client's address (so you can know who is connected).

// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1TcpListener.php#a59a1db5b6f4711a3e57390da2f8d9630

/*
// Create a listener socket and make it wait for new
// connections on port 55001
sf::TcpListener listener;
listener.listen(55001);

// Endless loop that waits for new connections
while (running)
{
    sf::TcpSocket client;
    if (listener.accept(client) == sf::Socket::Done)
    {
        // A new client just connected!
        std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
        doSomethingWith(client);
    }
}
*/

// https://www.thegeekstuff.com/2011/12/c-socket-programming/

// https://programmer.help/blogs/an-example-of-c-socket-programming-under-linux.html

//
// Detecting tcp client disconnect
//
//

// TODO:
// 1.
// Detecting broken connection
//
// 2.
// Move IP and Port parameters as arguments
//
// 3.
// Make 2 separate threads for server and gpsdev, or server could be as a main process ?
// What is a best way to exit, if it will be daemon ? By signal ?
//
//

// Current Open Points:
//
// 1.
// Server is not working, probably after put the code into pthread
// Cannot debug because debugger do not found pthread sources.


#include <iostream>
#include <SFML/Network.hpp>
#include <pthread.h>
#include "sfml_serv.hpp"
#include "server.hpp"
#include "gpsdev.hpp"



pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;


int main(int argc, char* argv[])
{
	/*
	std::cout << "Server is starting" << std::endl;
	Server();
	std::cout << "Server is finished" << std::endl;
	*/

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, Server, NULL);
	pthread_create(&thread2, NULL, Gpsdev, NULL);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	exit(0);

}


#if 0

#include <iostream>
#include <SFML/Network.hpp>
#include "server.hpp"

const unsigned short PORT = 5000;
const std::string IPADDRESS("127.0.0.1");//change to suit your needs
//sf::IPAddress Address5 = sf::IPAddress::LocalHost;

std::string msgSend;

sf::TcpSocket socket;
sf::Mutex globalMutex;
bool quit = false;

void DoStuff(void)
{
	static std::string oldMsg;
	while(!quit)
	{
		sf::Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		globalMutex.unlock();

		socket.send(packetSend);

		std::string msg;
		sf::Packet packetReceive;

		socket.receive(packetReceive);
		if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
		{
			std::cout << msg << std::endl;
			oldMsg = msg;
		}
	}
}

void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);

	/*
	if (listener.listen(53000) != sf::Socket::Done)
	{
	    // error...
	}
	*/

	listener.accept(socket);
	/*
	if (listener.accept(client) != sf::Socket::Done)
	{
	    // error...
	}
	*/

	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

bool Client(void)
{
	if(socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}

void GetInput(void)
{
	std::string s;
	std::cout << "\nEnter \"exit\" to quit or message to send: ";
	getline(std::cin,s);
	if(s == "exit")
		quit = true;		// Why quit is not guarded with mutex ?
	globalMutex.lock();
	msgSend = s;
	globalMutex.unlock();
}


int main(int argc, char* argv[])
{
	sf::Thread* thread = 0;

	char who;
	std::cout << "Do you want to be a server (s) or a client (c) ? ";
	std::cin  >> who;

	if (who == 's')
		Server();	// it is listening and wait for connection, if connected with client it return socket and goes forward.
	else
		Client();

	thread = new sf::Thread(&DoStuff);
	thread->launch();

	while(!quit)
	{
		GetInput();
	}

	if(thread)
	{
		thread->wait();
		delete thread;
	}
	return 0;
}

#endif
