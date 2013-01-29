
#include "Transliteration.h"
#include<string>
#include<iostream>

static string prefix[][2] = {   {"k","&#x0915;"},
                                {"kh","&#x0916;"},
                                {"g","&#x0917;"},
                                {"gh","&#x0918;"},
                                {".n","&#x0919;"},{"nG","&#x0919;"},
                                {"ch","&#x091a;"},
                                {"chh","&#x091b;"},
                                {"j","&#x091c;"},
                                {"jh","&#x091d;"},
                                {".y","&#x091e;"},
                                {".t","&#x091f;"},{"T","&#x091f;"},
                                {".th","&#x0920;"},{"Th","&#x0920;"},
                                {".d","&#x0921;"},{"D","&#x0921;"},
                                {".dh","&#x0922;"},{"Dh","&#x0922;"},
                                {"nD","&#x0923;"},
                                {"t","&#x0924;"},
                                {"th","&#x0925;"},
                                {"d","&#x0926;"},
                                {"dh","&#x0927;"},
                                {"n","&#x0928;"},
                                {"p","&#x092a;"},
                                {"f","&#x092b;"},
                                {"b","&#x092c;"},
                                {"bh","&#x092d;"},{"v","&#x092d;"},
                                {"m","&#x092e;"},
                                {"y","&#x092f;"},
                                {"r","&#x0930;"},
                                {"l","&#x0932;"},
                                {"w","&#x0935;"},
                                {"sh","&#x0936;"},
                                {"S","&#x0937;"},
                                {"s","&#x0938;"},
                                {"h","&#x0939;"},
                                {"Gy", "&#x091c;&#x094d;&#x091e;"}
                              /*{"ksh", "&#x0915;&#x094d;&#x0937;"},
                                {"tr", "&#x0924;&#x094d;&#x0930;"},
                                {"gy", "&#x091c;&#x094d;&#x091e;"},
                                {"shr", "&#x0936;&#x094d;&#x0930;&#x0940;"} */ //check if necessary
                           };


static string  suffix[][2] = {  {"" ,"&#x094d;"},
                                {"a",""},
                                {"aa","&#x093e;"},
                                {"i","&#x093f;"},
                                {"ii","&#x0940;"},
                                {"u","&#x0941;"},
                                {"uu","&#x0942;"},
                                {"e","&#x0947;"},
                                {"ai","&#x0948;"},
                                {"o","&#x094b;"},
                                {"au","&#x094c;"},
                              //{"ah","&#x0903;"} //this may cause problem, : is trivial
                              };

static string independent[][2] = {  {"OM","&#x0950;"},
                                    {"a", "&#x0905;"},
                                    {"aa", "&#x0906;"},
                                    {"i", "&#x0907;"},
                                    {"ii", "&#x0908;"},
                                    {"u", "&#x0909;"},
                                    {"uu", "&#x090a;"},
                                    {"ae", "&#x090f;"},    {"e", "&#x090f;"},
                                    {"ai", "&#x0910;"},
                                    {"o", "&#x0913;"},
                                    {"au", "&#x0914;"},
                                    {"am", "&#x0905;&#x0902;"},
                                 // {"ah", "&#x0905;&#x0903;"}, //causes problem
                                    {" ", " "},
                                    {"N", "&#x0902;"},  //anusar
                                    {"`", "&#x0901;"}, {"'","&#x0901;"}, //chandra bindu
                                    {"Ri", "&#x0960;"},
                                    {"0","&#x0966;"},
                                    {"1","&#x0967;"},
                                    {"2","&#x0968;"},
                                    {"3","&#x0969;"},
                                    {"4","&#x096a;"},
                                    {"5","&#x096b;"},
                                    {"6","&#x096c;"},
                                    {"7","&#x096d;"},
                                    {"8","&#x096e;"},
                                    {"9","&#x096f;"},
                                    {".", "&#x0964; "},
                                 // {". ", "&#x0964; "},
                                 // {" . ", " &#x0964; "},
                                 // {"&","&amp;"}, //can be used for html support
                                    {"[","["}
                                  };

#define PREFIX_COUNT sizeof(prefix)/(2*sizeof(string))
#define SUFFIX_COUNT sizeof(suffix)/(2*sizeof(string))
#define INDEPENDENT_COUNT sizeof(independent)/(2*sizeof(string))

translit::translit()
{
    load();
}


void translit::load()
{
    maxKeyLen = 0;
    for(int i = 0;i<PREFIX_COUNT;i++)
    {
        for(int j  = 0;j<SUFFIX_COUNT;j++)
        {
            if( (prefix[i][0] + suffix[j][0]).size() > maxKeyLen)
                maxKeyLen = (prefix[i][0] + suffix[j][0]).size();
            mapping[ prefix[i][0]+suffix[j][0] ] = prefix[i][1] + suffix[j][1];

        }
    }

    for(int i = 0;i<INDEPENDENT_COUNT;i++)
    {
        if(independent[i][0].size() > maxKeyLen)
            maxKeyLen = independent[i][0].size();
        mapping[independent[i][0]] = independent[i][1];
    }

    for(int i = 0;i<PREFIX_COUNT;i++) //for convenient, don't require "a" sound at last
    {
        if( (prefix[i][0] + " ").size() > maxKeyLen)
            maxKeyLen = (prefix[i][0] + " ").size();
        mapping[ prefix[i][0] + " " ] = (prefix[i][1] + suffix[1][1] + " ");
    }


}


string translit::toDevnagari(string roman)
{
    string result = "";
    int cur = 0;
    int end = roman.size();
    bool found = false;

    unordered_map<string,string>::iterator it;
    while(cur < end)
    {
        for(int i = maxKeyLen;i>=1;i--)
        {
            if(i<=(end - cur) && !found)
            {
                it = mapping.find(roman.substr(cur,i));

                if(it!=mapping.end())
                {
                    if(it->second == "[")  //support roman/english/html tags in between
                    {
                        cur++;
                        while(roman[cur]!=']' && (cur < end))
                        {
                            result+=roman[cur];
                            cur++;
                        }
                    }
                    else
                    {
                        result += it->second;
                        found = true;
                        cur += i;
                    }
                }
             }
        }

        if(found == false)
        {
            if(roman[cur] == '/')
            {
                cur++;
                while(cur < end)
                {
                    if(roman[cur] != ' ')
                    {
                        result+= roman[cur];
                        cur++;
                    } else {
                        break;
                    }
                }
            }
            if(cur < end)
                if(roman[cur]!= ']')
                    result += roman[cur];
            cur++;
        }
        found = false;

    } //end main while

    return result;
}

