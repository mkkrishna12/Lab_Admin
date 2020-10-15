enum os{LINUX,WINDOWS,NONE};

struct  _user_info {
	char PRN[30];
};

struct _client_info {
	char ip[30];
	char port[10];
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

union core_msg {
	struct _user_info user_info;
	struct _client_info client_info;
	struct _script script;
	struct _file_transfer file;
	struct _loopback_message loopback_massage;
};

struct _data{
	char ip[20];
	char port[6];
	enum os os_type;
	union core_msg data;
};

struct _message {
	long int message_type;
	struct _data message_data;
};
