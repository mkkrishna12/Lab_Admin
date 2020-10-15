#include <bits/stdc++.h>
#include "dataset.h"
using namespace std;

map<KEY, VALUE*> Database;

void ClientInit(struct _message something)
{
  KEY ClientInfo;
  ClientInfo.IP=IP;
  ClientInfo.PORT=PORT;
  
  Database[ClientInfo] = new VALUE;

  Database[ClientInfo]->TIMESTAMP.DATE=DATE;
  Database[ClientInfo]->TIMESTAMP.TIME=TIME;
  
}

void UserInit(struct _message something)
{
  // User Info In map
}

int main()
{


 
  return 0;
}
