struct  _user_info {
    int TYPE;
	char PRN[30];
	char DATE[15];
	char TIME[15];
	char YEAR[6];
	char BRANCH[30];
	char NAME[50];
};

struct _script {
	char command[1024];
};

struct _file_transfer {
	char file_name[100];
	char file_buffer[1024];
};

struct _loopback_message {
	char PRN[30];
	char DATE[15];
	char TIME[15];
	char YEAR[6];
	char BRANCH[30];
	char NAME[50];
};

struct _server_data{
    char ip[20];
    char port[6];
};

union _control_message{
    struct _server_data server_data;
};

union _msg {
	struct _user_info user_info;
	struct _script script;
	struct _file_transfer file;
	struct _loopback_message loopback_massage;
	union _control_message control_message;
};

struct core_msg{
    long int msg_type;
    union _msg msg;
};

struct _data{
	char ip[20];
	char port[6];
	int os_type;
	struct core_msg data;
};

struct _message {
	long int message_type;
	struct _data message_data;
};
