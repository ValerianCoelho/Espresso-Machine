#include <iostream>
#include <ios>
#include <string>
using namespace std;

string multiplyInput(string text = "", int width = 0){
    string newText = "";
    for(int i=0; i<width; i++){
        newText += text;
    }
    return newText;
}

void alignCenter(string text = "", int width = 0, string leftText = "", string rightText = ""){
    int left = (width - text.length())/2;
    int right = width - (left + text.length());
    cout << leftText;
    cout.width(left + text.length());
    cout.fill(' ');
    cout << text;
    cout.width(right);
    cout << "";
    cout << rightText;
}

string returnCenterAligned(string text = "", int width = 0, string leftText = "", string rightText = ""){
    int left = (width - text.length())/2;
    int right = width - (left + text.length());
    return leftText + multiplyInput(" ", left) + text + multiplyInput(" ", right) + rightText;
}

void alignLeft(string text = "", int width = 0, string leftText = "", string rightText = ""){
    cout << leftText;
    cout.width(width);
    cout << left;
    cout << text;
    cout << rightText;
}

string returnLeftAligned(string text = "", int width = 0, string leftText = "", string rightText = ""){
    return leftText + text + multiplyInput(" ", width - text.length()) + rightText;
}

string formatFloat(float num){
    string formatedNumber = "";
    string newNum = to_string(int(num * 100));
    if(num == 0)
        formatedNumber = formatedNumber + to_string(int(num)) + "." + "00";
    else
        formatedNumber = formatedNumber + to_string(int(num)) + "." + newNum[newNum.length()-2] + newNum[newNum.length()-1];
    return formatedNumber;
}