struct _timeStamp{
  string DATE;
  string TIME;
};

struct _user{
  string YEAR;
  string BRANCH;
  string PRN;
  string NAME;
  struct _timeStamp TIMESTAMP;
};

typedef struct _key{
  string IP;
  string PORT;
  struct _timeStamp TIMESTAMP;
} KEY;

typedef struct _value{
  struct _user* USER_DATA;
} VALUE;
