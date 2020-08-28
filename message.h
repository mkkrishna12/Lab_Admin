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

struct _file_trasfer {
	char file_name[200];
	char file_buffer[1024];
};

struct _loopback_message {
	char data[1024];
};

union _data {
	struct _user_info user_info;
	struct _client_info client_info;
	struct _script script;
	struct _file_transfer file_transfer;
	struct _loopback_message loopback_massage;
};

struct _message {
	long int message_type;
	union _data message_data;
};
