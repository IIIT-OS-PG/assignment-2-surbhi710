#include<bits/stdc++.h>
#include<fstream>
#include <iostream>
#include<sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
using namespace std;
char *temp[20];
char r[50];

class create_socket{
public:
	char *ip;
	int port;
create_socket(){port=0;}

//***********used for seperating space**********************

void input(string s){
	strcpy(r,s.c_str());
	char *p = strtok(r," ");
	temp[0]=p;

	int i=0;
	while(p){
		p = strtok(NULL," ");
		temp[++i]=p;
	}
}
//************reading port and ip for tracker1*****************
void initialize1(){
	ifstream fin;
	string line1,line2;
	fin.open("tracker_info.txt", std::ios::out);
	int i=0;
	if(i==0) {
		getline(fin,line1);
		input(line1);
		i++;
	}
	ip = temp[0];
	port = stoi(temp[1]);
	fin.close();
//	cout<<"ip and port of tracker1 is:"<<ip<<" "<<port<<endl;
}

//**********reading port and ip for tracker2***************
void initialize2(){
	ifstream fin;
	string line1,line2;
	fin.open("tracker_info.txt", std::ios::out);
	int i=1;
	if(i==1) {
		getline(fin,line1);
		input(line1);
		i++;
	}
	ip = temp[0];
	port = stoi(temp[1]);
	fin.close();
//	cout<<"ip and port of tracker2 is:"<<ip<<" "<<port<<endl;
}

void initialize3(int portno){
	ip= "127.0.0.1";
	port =portno;
}

};