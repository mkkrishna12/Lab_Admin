struct  _user_info {
	char PRN[30];
};

struct _script {
	char command[1024];
};

struct _file_transfer {
	char file_name[100];
	char file_buffer[1024];
};

struct _loopback_message {
	char data[1024];
};

union _msg {
	struct _user_info user_info;
	struct _script script;
	struct _file_transfer file;
	struct _loopback_message loopback_massage;
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
