
#include "tracker.h"
#include "create_socket.cpp"

struct socket//socket==data
{
    string IP, port;
};
map<string, vector<struct socket>> socket_info;
vector<string>command;

//********creating socket for tracker**********************************
void create(char *ip,int port){

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==0){
			perror("socket failed");
			exit(EXIT_FAILURE);
		}
     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr(ip);
     serv_addr.sin_port = htons(port);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
              perror("binding error");
     if(listen(sockfd,5)<0){
     	perror("listen failed");
     	exit(EXIT_FAILURE);
     }
}


//*****function to provide application to the server********************
void *tracker_application(void *socket_desc){
	int newsockfd = *(int *)socket_desc;
	while(1){

		char buffer[1024]={0};//for sharing files with the tracker
		int l = read(newsockfd,buffer,1024);
		int data0=stoi(string(buffer));

		if(data0 == 1){//means create account 
			bzero(buffer,1024);
			int rc1 = read(newsockfd,buffer,1024);
			string client_msg;

			string data1=string(buffer);//storing the incomming string in data 
			vector<pair<string,string>>v1;
			bzero(buffer,1024);
			int rc2 = read(newsockfd,buffer,1024);
			string data2=string(buffer);

			v1.push_back(make_pair(data1,data2));//storing account info
		}
		else if(data0==2){ //downloading details from tracker
			bzero(buffer,1024);
			int rc1 = read(newsockfd,buffer,1024);
			string client_msg;

			string data1=string(buffer);
			vector<string>v2;
			v2.push_back(data1);
			buffer[1024] = {0};
            string hash;
            msg = "";
            cmd = stringsplit(string(buffer), ',');
            command = cmd[0];
            hash = cmd[1];
            vector<struct Data> v = storeData[hash];
            string hello = new char[msg.length() + 1];
            strcpy(hello, msg.c_str());
            send(new_socket, hello, strlen(hello), 0); // Send data to client.
        }
	}
	return socket_desc;
}

//
int main(int argc,char *argv[]){

	int sockfd, newsockfd, portno,newsocket;
	socklen_t clilen;
	char buffer[512];
	int opt = 1;
	struct sockaddr_in serv_addr, cli_addr;
	 struct sockaddr_in address;

	int addrlen = sizeof(address);
	create_socket tracker1;
	create_socket tracker2;
	portno = stoi(argv[1]);

	if(argv[1] == "1"){
		tracker1.initialize1();
		create(tracker1.ip,tracker1.port);
	}
	else{
		tracker2.initialize2();
		create(tracker2.ip,tracker2.port);
	}

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sockfd, 10) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }serverservice
    pthread_t thread_id;
    while (1)
    {
        if ((newsocket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        // Every time new thread to serve each client and pass socket number as argument.
        int *arg = (int *)malloc(sizeof(*arg));
        *arg = newsockfd;
        pthread_create(&thread_id, 0, tracker_application, arg);
    }
    cout << "tracker Closed!!!" << endl;
}

