#include <iostream>
#include <iomanip>
#include <istream>
#include <string>

using namespace std;


void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}



int main(){
	//Output
	cout << "Hello World" << endl;
	int x = 50;
	cout << "There are " << x << " ways to leave your lover." << endl;
	double dollars = 2.0;
	cout << "Give me $" << setw(10) << fixed << setprecision(2) << dollars << setw(0) << "!" << endl;
	//Intput

	return 0;
	cout << "Enter the x, y, and x values: ";
	int y = 0;
	int z = 0;
	cin >> x >> y >> z;

	int a = 5;
	int b = 9;
	cout << a << b << endl;
	swap(a,b);
	cout << a << b << endl;


}
