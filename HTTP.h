#ifndef HTTP_H
#define HTTP_H

#define ABSOLUTE_PATH "/home/sungho/project/flavor-cloud/web"

enum HTTPErrorCode{
    DEFAULT = 0,
    SUCCESS = 0,

    requestErrorCode = 100,
    fail_splitRequestStartLine,

    responseErrorcode = 200,
    fail_notFindFile,
    fail_noMatchContentType,
};

enum HTTPErrorCode getLastErrCode();

// request data structure
struct request_start{
    char * HTTP_method;
    char * request_target;
    char * HTTP_ver;
};

struct request{
    struct request_start startLine;
    char * header;
    char * body;
} ;

enum HTTPErrorCode splitRequest(struct request * target, char * str);


//response data structure
struct response_startLine{
    char * HTTP_ver;
    char * stat_code;
    char * stat_text;
};

struct response_header{
    char * content_type;
};


struct response{
    struct response_startLine startLine;
    struct response_header header;
    char * body;
};

int processGetRequest(int client_socket, struct request reqData);
int processPutRequest(int client_socket, struct request reqData);
int processStatRequest(int client_socket, struct request reqData);

#endif