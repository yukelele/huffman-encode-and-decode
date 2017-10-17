// Yuki Mano, ysm@umail.ucsb.edu, CS130B, Fall 2017

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>
#include <bitset> //MAY NOT NEED THIS
#include <cstdint> //may not need 
#include <cmath>

using namespace std;

int charToAscii(char character); // Converting a character to its corresponding ASCII value
string charToEncode(char c, map<string,string> encodedList); // Converting a character to its corresponding Encoded value
int binary_to_decimal(string num); 

int main( int argc, char* argv[]){

  // store the encoded list to a map
  ifstream encodedFile(argv[1]);  
  map<string, string> mapOfEncodedAscii;
  string line1;
  while (getline(encodedFile, line1))
    {
      istringstream iss(line1);
      string ascii_value;
      string encode_value;
      iss >> ascii_value;
      iss >> encode_value;

      mapOfEncodedAscii[ascii_value] = encode_value;  
    }  

  // read from stdin one character at a time
  int bit_count = 0;
  string bit_string = "";
  while (!cin.eof()) 
    {       
      char c = cin.get();
      if(!cin.eof()){
        string encode = charToEncode(c, mapOfEncodedAscii);
        
        bit_string += encode;
        bit_count += encode.length();    

        while(bit_count >= 8){
          string byte_string = bit_string.substr(0,8);
    
          bit_count -= 8;
          bit_string = bit_string.substr(8, bit_count); 

          //cout << byte_string << " is the binary code for : "  << binary_to_decimal(byte_string) << endl;

          cout << char(binary_to_decimal(byte_string));
        }
      }
    }
    for (int i=0; i<bit_count; i++){
      bit_string += "0";
    }
    //cout << binary_to_decimal(bit_string) << endl;
    cout << char(binary_to_decimal(bit_string));

    //cout << int(char(binary_to_decimal("10000000"))) << endl;

  return 0;
}

// Converting a character to its corresponding ASCII value
int charToAscii(char character){
  int ascii = static_cast<int>(character);
  if(ascii < 0) return (256 + ascii);
  else return ascii;
}

// Converting a character to its corresponding Encoded value
string charToEncode(char c, map<string,string> encodedList){
  int value = charToAscii(c);
  string ascii = to_string(value);
  return encodedList[ascii];
}

int binary_to_decimal(string num)
{
    int result = 0;
    for(int i=0; i<num.length(); i++){      // length should not be more than 8
      result += stoi(num.substr(num.length()-1-i, 1)) * pow(2, i);
    }
    return result;
}


