/************************************************************************************************
Author: Chaman Thapa.

Note: This is the first prototype working version. For efficiency hash_map can be used.

*************************************************************************************************/



#ifndef TRANSLITERATION_H
#define TRANSLITERATION_H


#include<string>
#include<iostream>
#include<map>
//#include<ext/hash_map>

using namespace std;
//using namespace __gnu_cxx;


class translit{
 public:
    translit();
    string toDevnagari(string roman);
    void load();


 private:
    map<string,string> mapping;
    unsigned int maxKeyLen;


};

#endif

