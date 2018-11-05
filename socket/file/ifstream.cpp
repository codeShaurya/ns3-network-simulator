#include <bits/stdc++.h>
using namespace std;

// TODO : delimitation at line 19

int main()
{

  char *buf[100];
  ifstream file("file.txt");

  string s;
  while (getline(file, s))
  {
    cout << s << "\n";
  }

  cout << "This will read the file with a seprator : " << endl;
  while (getline(file, s, ' '))
  {
    cout << s << "\n";
  }
  return 0;
}
