#include "../tracker1/create_socket.cpp"
#include "client_header.h"
#include "split_files.cpp"
using namespace std;

string file_name="A";
string hashf,p1;
string ip1="127.0.0.1";
string client_ip="127.0.0.1", server_ip1, server_ip2;
//*compile it using [g++ client.cpp -Wall -lcrypto -o client]
//*run it using [./client 20005 abc.mp3]

//const char* logfile;
int sockfd, n;
char buffer[512];

//*******main client function call where client start and communicate with tracker******************************
void create(int portno){
	char buff[512];
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        perror("ERROR opening socket");
  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);
    //convert ip addres from text to binary form.
 	//inet_pton(AF_INET, tracker2.ip, &serv_addr.sin_addr);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        perror("ERROR connecting");
  		bzero(buff,512);
}
//function for closing socket**************************************************************
void close(){
	close(sockfd);
	exit(1);
}

//function to send file info to the tacker**************************
void file_upload(string s1,int d){
	
	FILE *fp = fopen(filename,"rb");
        fseek(fp,0,SEEK_END);
        long long size=ftell(fp);
        rewind(fp);
        if(size<524288)
        	send_file(fp);
        else{
        	string file_name="A";
        	char* name = &file_name[0];
        	file_piece(filename,name,size,524288);
        	string str;
        	str=hashtotal();
        	p1=concat(str,argv[1],ip1);
        	}
	write(sockfd,&d,sizeof(int));
	wait(5);
	write(sockfd,&s1,sizeof(string));
	cout<<"file info is send to tracker"<<endl;
	close(sockfd);

}

//function to download files**********************************************
void *download(void *args){
struct arg_struct args = *((struct arg_struct *)arg);
    int sock1 = 0;
    string msg;
    char *str2;
  
    struct sockaddr_in serv_addr1;
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
   
    vector<pair<string,int>>download_list;
  /*  memset(&serv_addr1, '0', sizeof(serv_addr1));

    serv_addr1.sin_family = AF_INET;
    serv_addr1.sin_port = htons(stoi(string(args.port)));
    create(args.port);

    connect(sock1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1));
    */ 
    char *buffer1;
    /*long int n;
    buffer1 = new char[chunksize];
    send(sock1, args.fname, strlen(args.fname), 0);
  
    while(n>0){
        buffer1 = new char[chunksize];
        n = read(sock1, buffer1, chunksize);
        createFile.write(buffer1, n);
    }
    createFile.close();
    
    cout << "File downloaded" << endl;
    vector<string> temp;

    temp.push_back("share");
    download_list.first="share";

    temp.push_back(fs);
    download_list.second=sock1;
    temp.push_back(mt);*/
    msg = share(temp, client_ip, server_ip1, server_ip2);
   
    str2 = new char[msg.length() + 1];
    strcpy(str2, msg.c_str());
    send(args.sock, str2, strlen(str2), 0);
    read(args.sock, buffer1, 1024);
  
    return arg;
}

//function to concate hash+ip+port****************************************
string concat(string str,string port,string ip2){
	string s= 1+" "+str+" "+port+" "+ip2;
	cout<<s;
	return s;
}

//function for sending files,if file size is less than 512kb.
void send_file(FILE *f){
	int words=0;
	char c;
	while((c=getc(f))!=EOF)			//counting words in the file
    {	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')
		words++;	
	}    
      
	write(sockfd, &words, sizeof(int));
     	rewind(f);
       
    char ch ;//for writing on to the server 
       while(ch != EOF){
		fscanf(f , "%s" , buffer);
		write(sockfd,buffer,512);
		ch = fgetc(f);//update the ch
      }
	printf("The file was sent successfully");
	close();
}

//function for sending client information to tracker*****************
void create_account(vector<pair<string,string>>&v,int port1,int l=1){
	string user = v[0].first;
	string pass = v[0].second;
	create(port1);
	//send(sockfd,user,50,0);
	write(sockfd,&l,sizeof(int));
	sleep(5);
	write(sockfd, &user, sizeof(string));
	sleep(10);
	//send(sockfd,pass,50,0);
	write(sockfd, &pass, sizeof(string));
	cout<<"user and password is sent successfully"<<endl;
	close();

}


int main(int argc,char *argv[]){

	//create_socket client_socket;
	create_socket  tracker1;
	create_socket  tracker2;
	char* filename=argv[2];
//enter tracker's port to communicate with tracker
	int p=stoi(argv[1]);
	create(p);
	tracker1.initialize1();
	tracker2.initialize2();
	server_ip2=tracker1.ip;
	server_ip1=tracker2.ip;
	
	pthread_t server_thread;
	//if(pthread_create(&thread_id,NULL,peer_service,))

	pthread_create(&server_thread, 0, serverservice, (void *)&client_ip);
	struct sockaddr_in serv_addr;
	struct hostent *server;
	string command;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        perror("ERROR opening socket");
  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);
    //convert ip addres from text to binary form.
 	//inet_pton(AF_INET, tracker2.ip, &serv_addr.sin_addr);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        perror("ERROR connecting");
  		bzero(buff,512);


  		string s="";
  		vector<string>commandvector;
  		commandvector.clear();

  		getline(cin,command);
  		commandvector=command;

  	void *serverservice(void *socket_des){
  		while(1){
  		if(commandvector[0]==1){
  			char buffer[512];
  			char *str;
  			string input=share(commandvector,client_ip,server_ip1,server_ip2);
  			str=new char[input.length()+1];
  			strcpy(str,input.c_str());
  			send(sockfd,str,strlen(str),0);
  			read(sockfd,buffer,1024);
  			cout<<string(buffer)<<endl;

  		}
		//string cmd;
		string cmd;
	
		  cout<<"enter choice"<<endl;
 	    cout<<"1. create account"<<endl;
  	 cout<<"2. uploading files"<<endl;
  	 cout<<"3. download files"<<endl;
  
	int choice;
	cin>>choice;
	//writelog("user command: "+ choice);
	switch(choice){
		case 1:{
			string user,password;
			cout<<"enter user: "<<endl;
			cin>>user;
			cout<<"enter password: "<<endl;
			cin>>password;
			vector<pair<string,string>>v;
			v.push_back(make_pair(user,password));
			create_account(v,p,1);}
			break;
		case 2:{
			FILE *fp = fopen(filename,"rb");
        fseek(fp,0,SEEK_END);
        long long size=ftell(fp);
        rewind(fp);
        if(size<524288)
        	send_file(fp);
        else{
        	string file_name="A";
        	char* name = &file_name[0];
        	file_piece(filename,name,size,524288);}
        	string str;
        	str=hashtotal();
        	p1=concat(str,argv[1],ip1);
        	file_upload(p1,2);
        	}
        	break;
        case 3:{
        	download(args);
        }
        break;
        }
       return 0;
  }