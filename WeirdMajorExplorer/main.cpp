//
//  main.cpp
//  WeirdMajorExplorer
//
//  Created by Tony on 06/12/2017.
//  Copyright © 2017 Tony. All rights reserved.
//
// English words are from https://github.com/dwyl/english-words

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int getDistance(const string &strA, const string &strB){
    /*if(abs((int)(strA.length()-strB.length()))>1){
        return -1;
    }*/
    if(strA.length() != strB.length()){
        return -1;
    }
    int dif = 0;
    for(int i = 0; i < strA.length(); i++){
        if(strA[i]!=strB[i]){
            dif++;
        }
    }
    return dif;
    //return getDistanceHelper(strA, strB, 0, (int)strA.length()-1, 0, (int)strB.length()-1);
}

string process(string str){
    for(int i = 0;i < str.length();i++){
        if(str[i]>='A'&&str[i]<='Z'){
            str[i]-='A'-'a';//tolower
        }else if(str[i]<'a'||str[i]>'z'){
            str[i] = ' ';//make it a space
        }
    }
    return str;
}

void createDictVector(vector<string> &v, string dictFileName){
    ifstream f;
    f.open(dictFileName);
    if(!f){
        printf("Unable to open dictionary file.\n");
        return;
    }
    string word;
    while(f>>word){
        v.push_back(word);
    }
}

void computePossibleResult(string major, vector<string> &dict){
    string word;
    istringstream majorStringStream(major);
    while(majorStringStream>>word){
        for(string wordInDict : dict){
            if(getDistance(word, wordInDict) == 1){
                cout<<word<<" : "<<wordInDict<<endl;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    //Credit to UChicago website
    string majors[] = {"Anthropology","Applied Mathematics, Mathematics","Archaeology and Art of the Ancient Near East, Near Eastern Languages and Civilizations","Architectural Studies, Art History","Art History","Astronomy and Astrophysics","Astrophysics, Physics","Big Problems","Biological Chemistry","Biological Sciences","Business","Cancer Biology, Biological Sciences","Catalan, Romance Languages and Literatures","Cellular and Molecular Biology, Biological Sciences","Chemistry","Chicago Studies","Cinema and Media Studies","Classical Hebrew Language and Civilization, Near Eastern Languages and Civilizations","Classical Studies","Clinical and Translational Science","Comparative Human Development","Comparative Literature","Comparative Race and Ethnic Studies","Computational Analysis and Public Policy","Computational and Applied Mathematics","Computational Neuroscience, Biological Sciences","Computer Science","Creative Writing","Cuneiform Studies, Near Eastern Languages and Civilizations","East Asian Languages and Civilizations","Ecology and Evolution, Biological Sciences","Economics","Education Professions","Egyptology/Egyptian Languages and Civilizations, Near Eastern Languages and Civilizations","Endocrinology, Biological Sciences","Engineering, Molecular","English and Creative Writing, English Language and Literature","English Language and Literature","Entrepreneurship","Environmental Science","Environmental and Urban Studies","French, Romance Languages and Literatures","Fundamentals: Issues and Texts","Gender and Sexuality Studies","Genetics, Biological Sciences","Geographical Studies","Geophysical Sciences","Germanic Studies","Global Studies","Health Professions","History","History, Philosophy, and Social Studies of Science and Medicine","Human Rights","Humanities","Immunology, Biological Sciences","Interdisciplinary Studies in the Humanities","International Relations","Islamic and Modern Middle Eastern Studies, Near Eastern Languages and Civilizations"};
    vector<string> dict;
    createDictVector(dict, "words_alpha.txt");
    for(int i = 0; i < sizeof(majors)/sizeof(string); i++){
    //int i = 0; //view one by one
        string originalMajor = majors[i];
        string major = process(originalMajor);
        //cout << major << endl;
        cout << "Possible result for " << originalMajor << ":" << endl;
        computePossibleResult(major, dict);
        cout << endl;
    }
    return 0;
}
