#include<bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <pthread.h>

using namespace std;

string convert_string(int n);//written in split_file
void file_piece(char *fullFilePath,char* name,long long size, unsigned long chunkSize);
string hashtotal();//return hash value of file
void client(int port,string s);

