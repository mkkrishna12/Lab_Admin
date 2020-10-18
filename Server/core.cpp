#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "dataset.h"
#include "message.h"

map<KEY, VALUE*> Database;

void ClientInit(struct _message something)
{
  KEY ClientInfo;
  ClientInfo.IP = string(something.message_data.ip);
  ClientInfo.PORT = string(something.message_data.port);

  Database[ClientInfo] = new VALUE;

  Database[ClientInfo]->TIMESTAMP.DATE = string(something.message_data.data.msg.user_info.DATE);
  Database[ClientInfo]->TIMESTAMP.TIME = string(something.message_data.data.msg.user_info.TIME);

}

void UserInit(struct _message something)
{
  KEY ClientInfo;
  ClientInfo.IP = string(something.message_data.ip);
  ClientInfo.PORT = string(something.message_data.port);

  Database[ClientInfo] = new VALUE;

  Database[ClientInfo]->USER_DATA->TIMESTAMP.DATE = string(something.message_data.data.msg.user_info.DATE);
  Database[ClientInfo]->USER_DATA->TIMESTAMP.TIME = string(something.message_data.data.msg.user_info.TIME);
  Database[ClientInfo]->USER_DATA->YEAR = string(something.message_data.data.msg.user_info.YEAR);
  Database[ClientInfo]->USER_DATA->BRANCH = string(something.message_data.data.msg.user_info.BRANCH);
  Database[ClientInfo]->USER_DATA->PRN = string(something.message_data.data.msg.user_info.PRN);
  Database[ClientInfo]->USER_DATA->NAME = string(something.message_data.data.msg.user_info.NAME);
}

int main()
{



  return 0;
}
