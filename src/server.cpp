/*
 * gpsdev.cpp
 *
 */


// Print it:
// https://www.sfml-dev.org/tutorials/2.5/network-packet.php


// TODO:
//
//


// Status:
//
// tcpip server working
//



#include <iostream>
#include <SFML/Network.hpp>
#include <windows.h> // Sleep()
#include "server.hpp"

#include "gpsdev._hpp"



static const unsigned short PORT = 5000;
static const std::string IPADDRESS("127.0.0.1");//change to suit your needs
//sf::IPAddress Address5 = sf::IPAddress::LocalHost;

char serv_buff[GPSDEV_BUFF_LEN];

static void printBuff(char *b)
{
	printf("%s\n", *b);
}


#if 0
void *Server(void *x_void_ptr)
{
	sf::TcpListener listener;
	sf::Socket::Status conStatus = sf::Socket::Error;
	sf::TcpSocket socket;
	sf::Mutex globalMutex;
	bool run = true;
	bool connection = true;
	std::size_t bytesSent = 0;

	for (;;)
	{
		memset(serv_buff, 0, GPSDEV_BUFF_LEN);

		conStatus = listener.listen(PORT);
		if(conStatus == sf::Socket::Done)
		{
			std::cout << "OK: listener.listen(PORT) == sf::Socket::Done" << std::endl;
		}
		else if(conStatus == sf::Socket::NotReady)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::NotReady" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Partial)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Partial" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Disconnected)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Disconnected" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Error)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Error" << std::endl;
			continue;
		}


		while (run)
		{
			std::cout << "Test accept 1" << std::endl;

			conStatus = listener.accept(socket);

			std::cout << "Test accept 2" << std::endl;

			if(conStatus == sf::Socket::Done)
			{
				std::cout << "OK: listener.accept(socket) == sf::Socket::Done" << std::endl;
			}
			else if(conStatus == sf::Socket::NotReady)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::NotReady" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Partial)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Partial" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Disconnected)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Disconnected" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Error)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Error" << std::endl;
				//continue;
			}


			std::cout << "Test accept 3" << std::endl;


			while (connection)
			{
				pthread_mutex_lock( &condition_mutex );
				pthread_cond_wait( &condition_cond, &condition_mutex );
				// todo: perhaps GPSDEV_GetMsg(buff) shoudl be here ?
				pthread_mutex_unlock( &condition_mutex );
				// prepare msg
				GPSDEV_GetMsg(serv_buff);

				// send msg
				// This function i sblocking and will fail if the socket is not connected.
				//Status sf::TcpSocket::send(const void * data, std::size_t size, std::size_t &sent)
				conStatus = socket.send(serv_buff, (size_t)GPSDEV_BUFF_LEN, bytesSent);
				if(conStatus == sf::Socket::Done)
				{
					std::cout << "OK: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Done" << std::endl;
				}
				else if(conStatus == sf::Socket::NotReady)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::NotReady" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Partial)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Partial" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Disconnected)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Disconnected" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Error)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Error" << std::endl;
					break;
				}


				if (bytesSent != GPSDEV_BUFF_LEN)
				{
					std::cout << "ERR: bytesSent != BUFF_LEN" << std::endl;
				}

				// https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
				// Win32: Sleep(milliseconds) is what you what
				// Linux: sleep(seconds)
				Sleep(1);  // send data every 1 sec

			}// end while(connection)


		}	// end while(run)

	}	// end for(;;)

}
#endif



void GPSDEV_GetMsg(char *b)
{
	int len = 0;
	len = GPSDEV_BUFF_LEN - 1;		//todo: danger, hard set
	for(int i = 0; i < len; i++)
	{
		b[i] = 'A' + i;
	}
	//printBuff(b);	// there is any problem here and hangs out.
}


void Server()
{
	sf::TcpListener listener;
	sf::Socket::Status conStatus = sf::Socket::Error;
	sf::TcpSocket socket;
	sf::Mutex globalMutex;
	bool run = true;
	bool connection = true;
	std::size_t bytesSent = 0;

	for (;;)
	{
		memset(serv_buff, 0, GPSDEV_BUFF_LEN);

		conStatus = listener.listen(PORT);
		if(conStatus == sf::Socket::Done)
		{
			std::cout << "OK: listener.listen(PORT) == sf::Socket::Done" << std::endl;
		}
		else if(conStatus == sf::Socket::NotReady)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::NotReady" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Partial)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Partial" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Disconnected)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Disconnected" << std::endl;
			continue;
		}
		else if(conStatus == sf::Socket::Error)
		{
			std::cout << "ERR: listener.listen(PORT) == sf::Socket::Error" << std::endl;
			continue;
		}


		while (run)
		{
			std::cout << "Test accept 1" << std::endl;

			conStatus = listener.accept(socket);

			std::cout << "Test accept 2" << std::endl;

			if(conStatus == sf::Socket::Done)
			{
				std::cout << "OK: listener.accept(socket) == sf::Socket::Done" << std::endl;
			}
			else if(conStatus == sf::Socket::NotReady)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::NotReady" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Partial)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Partial" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Disconnected)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Disconnected" << std::endl;
				//continue;
			}
			else if(conStatus == sf::Socket::Error)
			{
				std::cout << "ERR: listener.accept(socket) == sf::Socket::Error" << std::endl;
				//continue;
			}


			std::cout << "Test accept 3" << std::endl;


			while (connection)
			{
				std::cout << "Test accept 4" << std::endl;

				GPSDEV_GetMsg(serv_buff);  //todo: proble here

				std::cout << "Test accept 5" << std::endl;

				// send msg
				// This function i sblocking and will fail if the socket is not connected.
				//Status sf::TcpSocket::send(const void * data, std::size_t size, std::size_t &sent)
				conStatus = socket.send(serv_buff, (size_t)GPSDEV_BUFF_LEN, bytesSent);

				std::cout << "Test accept 6" << std::endl;

				if(conStatus == sf::Socket::Done)
				{
					std::cout << "OK: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Done" << std::endl;
				}
				else if(conStatus == sf::Socket::NotReady)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::NotReady" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Partial)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Partial" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Disconnected)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Disconnected" << std::endl;
					break;
				}
				else if(conStatus == sf::Socket::Error)
				{
					std::cout << "ERR: socket.send(buff, (size_t)GPSDEV_BUFF_LEN, bytesSent) == sf::Socket::Error" << std::endl;
					break;
				}

				std::cout << "Test accept 7" << std::endl;

				if (bytesSent != GPSDEV_BUFF_LEN)
				{
					std::cout << "ERR: bytesSent != BUFF_LEN" << std::endl;
				}

				// https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
				// Win32: Sleep(milliseconds) is what you what
				// Linux: sleep(seconds)
				Sleep(1);  // send data every 1 sec

			}// end while(connection)


		}	// end while(run)

	}	// end for(;;)

}


