#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
using namespace std;

int main()
{
  
  list<int> data = {0,2,5,7,9};

  auto foobar = data.begin();

  for( ; foobar != data.end(); )
  {
    if (*foobar % 2 == 1)
    {
      foobar = data.erase(foobar);
    }
    else
    {
      ++foobar;
    }
  }  

  cout << data.size() << endl;
}
