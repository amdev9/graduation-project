
#include <list>
#include <map>

 #include <vector>
 
 #include <iostream>

#define DAY_HOURS	12
// Number of days in week
#define DAYS_NUM	6 //5

using namespace std;



 

int main(int argc, char* argv[]) { 
  

    cout << "argv[1] = " << argv[1] << endl; 


 	int r = 0;
	int dur =2;
	int nr = 2;
	while (r < 1) {
int day = rand() % DAYS_NUM;   // ---> 0 - 5
		int room = rand() % nr;

		int timeS = rand() % ( DAY_HOURS + 1 - dur );
cout << day<< " " <<room<<" " <<timeS << endl;
 r++;
}

return 0;
}