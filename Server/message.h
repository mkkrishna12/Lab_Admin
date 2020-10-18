struct  _user_info {
	char PRN[30];
	char NAME[100];
	char YEAR[10];
	char BRANCH[50];
	char DATE[20];
	char TIME[20];
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
