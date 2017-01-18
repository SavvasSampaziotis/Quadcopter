#include <iostream>
#include <String>

using namespace std;

int calculateHashCode(char s[]);

int main(){
	
	char header[2];
	char allHeaders[676][2];
	int allHC[676];// [17576];
	int h=0;
	for ( int i = 65; i <= 90; i++)
		for ( int j = 65; j <= 90; j++) 
		//	for ( int k = 65; k <= 90; k++) 
			{
				
				header[0] = (char) i;
				header[1] = (char) j;
			//	header[2] = (char) k;
			
				allHeaders[h][0] =  header[0];
				allHeaders[h][1] =  header[1];
				
				allHC[h] = calculateHashCode(header);
				cout<<"\n---------------------\n"<<header;
				for ( int b = 0; b < h; b++) 
					if(allHC[h]==allHC[b])
						cout<<" WARNING "<<allHeaders[b][0]<<allHeaders[b][1];
				
				h++;
			}
		

	return 0;
}

int calculateHashCode(char s[]) { // 90+1-65 = 26
  int r = 0;
  	for (int i = 0; i < 2; i++)
    r += ( s[i])*127^i;
    return r;
}
