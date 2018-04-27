#include <iostream>
#include <string>
//test
using namespace std;

string getName(int value);
string getTeens(int value);
string getTens(int value);


int main(){
	int value = 0;
	string output = "";
	cout << "Enter a number: (0-999) " << endl;
	cin >> value;
	if(value == 0){
		cout << "zero\n";
		return 0;
	}

	else if(value < 10){
		cout << getName(value) << endl;
	}
	else if(9 < value && value < 20 ){
		output = getTeens(value);
	}
	else if(19 < value){
		int tens = (value/10)%10;
		if(tens == 1){
			output += getTeens(value%100);
		}
		else{
			output += getTens(tens);
			int ones = value%10;
			if(ones != 0){
				output += " ";
				output += getName(ones);
			}
		}
	}
	else{
		cout << "shit broke man" << endl;
	}

	if( value >= 100){
		string hundreds = getName(value/100);
		hundreds = hundreds + " hundred ";
		output = hundreds + output;
	}

	cout << output << endl;

	return 0;
}


string getName(int value)
{
	switch( value )
	{
	case 1: return "one";
	case 3: return "three";
	case 2: return "two";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
	}

	return "";
}

string getTeens(int value)
{
	switch(value){
		case 10: return "ten";
		case 11: return "eleven";
		case 12: return "twelve";
		case 13: return "thirteen";
		case 14: return "fourteen";
		case 15: return "fifteen";
		case 16: return "sixteen";
		case 17: return "seventeen";
		case 18: return "eighteen";
		case 19: return "nineteen";
	}

	return "";
}

string getTens(int value){
	switch(value){
		case 2: return "twenty";
		case 3: return "thirty";
		case 4: return "fourty";
		case 5: return "fifty";
		case 6: return "sixty";
		case 7: return "seventy";
		case 8: return "eighty";
		case 9: return "ninety";
	}

	return "";
}
