#include <iostream>
#include <string>
using namespace std;

string MinWindowSubstring(string strArr[], int arrLength) {
  
  string minSubString;
  int characterIndexes[strArr[0].length()];
  int indexCntr = 0;
  for( int i = 0; i < strArr[0].length(); i++ )
  {
    for( int j = 0; j < strArr[1].length(); j++ )
    {
      if( strArr[0].charAt(i) == strArr[1].charAt(j) )
      {
        characterIndexes[indexCntr] = i;
      }
    }
    indexCntr++;
  }

  return strArr[0];

}

int main(void) { 
   
  // keep this function call here
  /* Note: In C++ you first have to initialize an array and set 
     it equal to the stdin to test your code with arrays. */

  string A[] = coderbyteInternalStdinFunction(stdin);
  int arrLength = sizeof(A) / sizeof(*A);
  cout << MinWindowSubstring(A, arrLength);
  return 0;
    
}