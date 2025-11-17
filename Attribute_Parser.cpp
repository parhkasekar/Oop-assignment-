#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore();
    
    map<string, string> attributes;
    string currentTag = "";
    vector<string> tagStack;
    
    for(int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        if(line.find("</") != string::npos) {
            if(!tagStack.empty())
                tagStack.pop_back();
        }
        else {
            stringstream ss(line);
            string temp;
            ss >> temp;
            
            string tagName = temp.substr(1);
            if(tagName[tagName.length()-1] == '>')
                tagName = tagName.substr(0, tagName.length()-1);
            
            tagStack.push_back(tagName);
            
            string fullTag = "";
            for(int j = 0; j < tagStack.size(); j++) {
                if(j > 0) fullTag += ".";
                fullTag += tagStack[j];
            }
            
            string attrName, equal, attrValue;
            while(ss >> attrName >> equal >> attrValue) {
                attrValue = attrValue.substr(1, attrValue.length()-2);
                attributes[fullTag + "~" + attrName] = attrValue;
            }
        }
    }
    
    for(int i = 0; i < q; i++) {
        string query;
        getline(cin, query);
        if(attributes.find(query) != attributes.end())
            cout << attributes[query] << endl;
        else
            cout << "Not Found!" << endl;
    }
    
    return 0;
}
