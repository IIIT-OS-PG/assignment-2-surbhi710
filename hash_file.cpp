//#include "client_header.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include <openssl/sha.h>
#include<string.h>
#include<cstring>
using namespace std;

//checking the length of the hash calculated****************************
void check_hash(string hash){
	if(strlen(hash)==20)
		cout<<"required length"<<endl;
	else
		cout<<"make lenth of hash as 20"<<endl;
}

//calculating hash functions*********************************************

std::string hash_chunk(char *chunk,int size){

	unsigned char hash[20];
	char buffer[SHA_DIGEST_LENGTH*2];//storing hash value
	//cout << "hi" << endl;
	SHA1((unsigned char*)chunk,size,hash);
	//cout << "bye\n";
	for(int i=0;i<SHA_DIGEST_LENGTH;i++)
		sprintf((char*)&(buffer[i*2]),"%02x",hash[i]);

	string hash_value;
	for(int i=0;i<20;i++){
		hash_value += buffer[i];
	}
	check_hash(hash_value);
	cout<<"***********************"<<endl;
	cout<<hash_value<<endl;
	cout<<"************************"<<endl;
return hash_value;
}
