#include <GHttp/GHttp.h>

#include <stdio.h>
#include <string.h>

void BuildHttpGet(GHttpRequest *req, const char *host, const char *path) {
    strcpy(req->Method, "GET");
    strcpy(req->Path, path);
    strcpy(req->Version, "HTTP/1.1");
    strcpy(req->Host, host);
    strcpy(req->UserAgent, "C-HTTP-Client/1.0");
    req->BodyLen = 0;
    req->Body[0] = '\0';
}

void BuildHttpPost(GHttpRequest *req, const char *host, const char *path,
                   const char *post_data) {
    strcpy(req->Method, "POST");
    strcpy(req->Path, path);
    strcpy(req->Version, "HTTP/1.1");
    strcpy(req->Host, host);
    strcpy(req->UserAgent, "C-HTTP-Client/1.0");
    strcpy(req->Body, post_data);
    req->BodyLen = strlen(post_data);
}

int RequestToString(GHttpRequest *req, char *out, int out_size) {
    int len = snprintf(out, out_size,
        "%s %s %s\r\n"
        "Host: %s\r\n"
        "User-Agent: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "\r\n"
        "%s",
        req->Method, req->Path, req->Version,
        req->Host,
        req->UserAgent,
        req->BodyLen,
        req->Body
    );
    return len;
}
