//With overloading 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class fileRA {
public:
    class Descriptor {
    public:
        Descriptor(fileRA &file, streampos pos) : file(file), pos(pos) {}

        Descriptor& operator=(char ch) {
            fstream& fstream = file.get_fstream();
            fstream.seekp(pos);
            fstream.put(ch);
            fstream.flush();
            return *this;
        }

        operator char() const {
            fstream& fstream = file.get_fstream();
            fstream.seekg(pos);
            return fstream.get();
        }

    private:
        fileRA &file;
        std::streampos pos;
    };

    fileRA(const string &filename) : filename(filename) {
        fileStream.open(filename, ios::in | ios::out | ios::binary);
        if (!fileStream.is_open()) {
            cerr << "Error opening file!" << endl;
        }
        fileStream.seekg(0, ios::end);
        fileSize = fileStream.tellg();
        fileStream.seekg(0, ios::beg);
    }

    ~fileRA() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    Descriptor operator[](streampos pos) {
        if (pos >= fileSize) {
            cerr << "Position out of bounds!" << endl;
        }
        return Descriptor(*this, pos);
    }

    size_t get_size() const { return fileSize; }

    fstream& get_fstream() { return fileStream; }

private:
    string filename;
    fstream fileStream;
    size_t fileSize;
};

int main() {
    fileRA fobj("input.txt");
    fobj[4] = 'A';

    for (unsigned int i = 0; i < fobj.get_size(); i++) {
        cout << fobj[i];
    }

    char c = fobj[1];
    cout << "\nChar is = " << c << endl;

    return 0;
}
//without overloading
/*
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class fileRA{
private:
  string fname;
  fstream myFile;
public:  
  fileRA(const string &filename){
    fname=filename;
    myFile.open(fname,ios::in|ios::out);
  }
  void write_at(int pos, char ch){
    myFile.seekp(pos);
    myFile.put(ch);
  }
  char read_at(int pos){
    myFile.seekg(pos);
    return myFile.get();
  }
  int get_size(){
    myFile.seekg(0, ios::end);
    return myFile.tellg();
  }
};
int main(){
  fileRA fobj("f.txt");
  fobj.write_at(4,'A');
  for(unsigned int i=0;i<fobj.get_size();i++){
    cout << fobj.read_at(i);
  }
  char c = fobj.read_at(4);
  cout << "Char is = " << c << std::endl;
}
*/
