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
} KEY;

typedef struct _value{
  struct _user* USER_DATA;
  struct _timeStamp *TIMESTAMP;
} VALUE;
