#include <bits/stdc++.h>
#include "dataset.h"
#include "message.h"
using namespace std;

map<KEY, VALUE*> Database;

void ClientInit(struct _message something)
{
  KEY ClientInfo;
  ClientInfo.IP = something.message_data.ip;
  ClientInfo.PORT = something.message_data.port;

  Database[ClientInfo] = new VALUE;

  Database[ClientInfo]->TIMESTAMP.DATE = something.message_data.data.msg.user_info.DATE;
  Database[ClientInfo]->TIMESTAMP.TIME = something.message_data.data.msg.user_info.TIME;

}

void UserInit(struct _message something)
{
  KEY ClientInfo;
  ClientInfo.IP=something.message_data.ip;
  ClientInfo.PORT=something.message_data.port;

  Database[ClientInfo] = new VALUE;

  Database[ClientInfo]->USER_DATA->TIMESTAMP.DATE = something.message_data.data.msg.user_info.DATE;
  Database[ClientInfo]->USER_DATA->TIMESTAMP.TIME = something.message_data.data.msg.user_info.TIME;
  Database[ClientInfo]->USER_DATA->YEAR = something.message_data.data.msg.user_info.YEAR;
  Database[ClientInfo]->USER_DATA->BRANCH = something.message_data.data.msg.user_info.BRANCH;
  Database[ClientInfo]->USER_DATA->PRN = something.message_data.data.msg.user_info.PRN;
  Database[ClientInfo]->USER_DATA->NAME = something.message_data.data.msg.user_info.NAME;
}

int main()
{



  return 0;
}
