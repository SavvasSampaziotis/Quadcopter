#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


class myClass{  // fantasou ayth san thn Command
	public:
		int A;
	public:
		myClass(int a) { A=a; };
		void printData(){
			cout<<"\n A = " << A ;
		};
		
};

int main() {
	
	cout<<"\n\n Start: \n";
	
	// Παραδειγμα Νο 1
	
	myClass class1( 500 );    //Φτιαχνει Αντικείμενο.   
	class1.printData();

	myClass* class2 = new myClass(10000);   // Φτιαχνει Pointer  που δείχνει στο Αντικείμενοpou
	class2->printData();
	
	/*
		class1 === object τυπου myClass (μεγεθος οσο τα members του. μπορει να ειναι και πολλα Byte αναλογα με το αντικειμενο )
		class2 === pointer of object τυπου myClass (μεγεθος οσο  enas pointer (nomizw 4byte. ston arduino mporei kai ligotera επειδη έχει λιγη μνήμη) )
	*/
	
	
	// Παραδειγμα Νο 2
	
	 // pinakas apo OBJECTS. to megethos einai 2*size_of(myClass). to objectArray[x] gyrnaei mia xoufta bYTE
	myClass objectArray[] = {  myClass(10),  myClass(200)}; 
	objectArray[0].printData();
	objectArray[1].printData();
	
	
	// Πίνακας απο pointers!!!! μεγεθος = 2*size_of(pointer) to opoio einai 2*4byte 'h kai ligotera....
	myClass* pointerArray[] = { new myClass(10), new myClass(200)} ;
	pointerArray[0]->printData();
	pointerArray[1]->printData();
	
	return 0;
}
