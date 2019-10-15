
#include "client_header.h"
#include "hash_file.cpp"

string convert_string(int n){
    ostringstream str1;
    str1 << n;
    return str1.str();
}
vector<string>v1;

string filehash;

void concatenate_hash(vector<string>v1);

void print (vector<string>&v1){
    for(auto i =v1.begin(); i!=v1.end(); ++i){
        cout<<*i<<endl;
    }
}

string hashtotal(){
    return filehash;
}

void file_piece(char *fullFilePath,char* name,long long size, unsigned long chunkSize){
    ifstream fileStream;
  
    fileStream.open(fullFilePath, ios::in | ios::binary);

    if (fileStream.is_open()) {
        ofstream output;

        int counter = 1;
        string fullname;
        //int n=20;
        char *buffer = new char[chunkSize];
        char* hash = new char[20];

        while (!fileStream.eof()) {
            fullname.clear();
            fullname.append(name);
            fullname.append(".");

           string p = convert_string(counter);
            fullname.append(p);

            output.open(fullname.c_str(),ios::out | ios::trunc | ios::binary);

            string hash_val;
            if (output.is_open()) { 
                fileStream.read(buffer,chunkSize);

                output.write(buffer,fileStream.gcount());
                //generating sha1 of each chunks
                
                output.close();
                hash_val=hash_chunk(buffer,chunkSize);
                v1.push_back(hash_val);
                filehash=filehash+hash_val;
                 counter++;
            }      
        }
        delete(buffer);
        print(v1);
        fileStream.close();

        cout << "Chunking complete! " << counter-1 << " files created." << endl;
   //   filehash include hash concatenated value of all chunks created.
        cout<<"generated SHA value after concatenating:  ";
        cout<<filehash<<endl;
        hashtotal(filehash);
}
