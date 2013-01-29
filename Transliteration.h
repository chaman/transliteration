/************************************************************************************************
Author: Chaman Thapa.
*************************************************************************************************/



#ifndef TRANSLITERATION_H
#define TRANSLITERATION_H


#include<string>
#include<iostream>
#include<unordered_map>


using namespace std;

class translit{
 public:
    translit();
    string toDevnagari(string roman);
    void load();


 private:
    unordered_map<string,string> mapping;
    unsigned int maxKeyLen;


};

#endif

