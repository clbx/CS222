#include <iostream>
#include "arraylist.h"

using namespace std;

int main(){

	ArrayList<int> list;
	list.add(5);
	list.add(7);
	list.add(9);
	list.add(-3);

	cout << "List at 2: " << list.get(2) << endl;

	list.remove(2);

	for(int i = 0; i < list.getSize(); ++i){
		cout << list.get(i) << " ";
	}
	cout << "\n" << endl;

}
