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
	
	// ���������� �� 1
	
	myClass class1( 500 );    //�������� �����������.   
	class1.printData();

	myClass* class2 = new myClass(10000);   // �������� Pointer  ��� ������� ��� �����������pou
	class2->printData();
	
	/*
		class1 === object ����� myClass (������� ��� �� members ���. ������ �� ����� ��� ����� Byte ������� �� �� ����������� )
		class2 === pointer of object ����� myClass (������� ���  enas pointer (nomizw 4byte. ston arduino mporei kai ligotera ������ ���� ���� �����) )
	*/
	
	
	// ���������� �� 2
	
	 // pinakas apo OBJECTS. to megethos einai 2*size_of(myClass). to objectArray[x] gyrnaei mia xoufta bYTE
	myClass objectArray[] = {  myClass(10),  myClass(200)}; 
	objectArray[0].printData();
	objectArray[1].printData();
	
	
	// ������� ��� pointers!!!! ������� = 2*size_of(pointer) to opoio einai 2*4byte 'h kai ligotera....
	myClass* pointerArray[] = { new myClass(10), new myClass(200)} ;
	pointerArray[0]->printData();
	pointerArray[1]->printData();
	
	return 0;
}
