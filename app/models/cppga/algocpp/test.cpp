/* strtok example */
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
 
#include <map>

using namespace std;

int main ()
{
  std::string sasdtr = "1/2/3";
  char* str = new char[sasdtr.length()+1];
  strcpy(str, sasdtr.c_str()); 
  
  int groups_col = 0;
  char * pch;

  map<int,int> arr;

  pch = strtok (str,"/");
  while (pch != NULL)
  {
    arr.insert(pair <int,int>(groups_col,atoi(pch)));  
    pch = strtok (NULL, "/");
    groups_col++;
  }


  cout << groups_col << "asd"<<endl;

  delete [] str;
  return 0;
}