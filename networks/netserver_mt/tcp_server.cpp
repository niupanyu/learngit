/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void  sigchld_handler(int sig)
{
    while(waitpid(-1, 0, WNOHANG) > 0)
        ;

    return;
}

void echo_handler(int fd);

class Task{
	private:
		int _id;

	public:
		Task(int number):_id(number){}

		void operator()(){
			echo_handler(_id);
			//yiled() ==> sleep(0);
			//boost::this_thread::yield();
		}
};

void echo_handler(int fd)
{
	int n;
    char buffer[256];
	auto start = boost::chrono::system_clock::now();
	while(1){
		bzero(buffer, 256);
		n = read(fd, buffer, 255);
		if(n < 0) error("error reading from socket");

		if(n == 0){
		    std::cout << "client close request." << std::endl;
			close(fd);
			auto end = boost::chrono::system_clock::now();

			auto duration = boost::chrono::duration_cast<boost::chrono::microseconds>(end - start);
			
			std::cout << "cost:" << duration.count() << " us" << std::endl;
			return;
		}

		std::cout << "recv:" << buffer << std::endl;
	}
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);

     signal(SIGCHLD, sigchld_handler); 
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     // /proc/sys/net/ipv4/tcp_max_syn_backlog
     listen(sockfd,128);

     while(1)
     {
         clilen = sizeof(cli_addr);
         newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
         
		 Task task(newsockfd);

		 boost::thread thrd(task);
	     thrd.detach();	 
    }
    
    close(sockfd);
    return 0; 
}
