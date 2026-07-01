 #pragma once
#include <GHttp/GHttpMethod.h>
#include <GHttp/GHttpStatusCode.h>
#include <GHttp/GHttpVersion.h>
/*
 *  https://www.rfc-editor.org/info/rfc9112
 *  https://www.rfc-editor.org/info/rfc9110
 *  https://www.rfc-editor.org/info/rfc9112/#name-request-line
 *  https://www.rfc-editor.org/info/rfc2616/#section-3.7
 */
namespace GNetwork
{
    /*
     * HTTP-message   = start-line CRLF
     *                  *( field-line CRLF )
     *                  CRLF
     *                  [ message-body ]
     *
     * Response       = Status-Line
     *                  *(( general-header | response-header | entity-header ) CRLF)
     *                  CRLF
     *                  [ message-body ]
     *
     * start-line     = request-line / status-line
     *
     * status-line    = HTTP-version SP status-code SP [ reason-phrase ]
     *
     * request-line   = method SP request-target SP HTTP-version
     *
     * request-target = origin-form
     *                  / absolute-form
     *                  / authority-form
     *                  / asterisk-form
     *
     * field-line     = field-name ":" OWS field-value OWS
     *
     * general-header = Cache-Control
     *                 | Connection
     *                 | Date
     *                 | Pragma
     *                 | Trailer
     *                 | Transfer-Encoding
     *                 | Upgrade
     *                 | Via
     *                 | Warning
     *
     * response-header = Accept-Ranges
     *                 | Age
     *                 | ETag
     *                 | Location
     *                 | Proxy-Authenticate
     *                 | Retry-After
     *                 | Server
     *                 | Vary
     *                 | WWW-Authenticate
     *
     * entity-header  = Allow
     *                | Content-Encoding
     *                | Content-Language
     *                | Content-Length
     *                | Content-Location
     *                | Content-MD5
     *                | Content-Range
     *                | Content-Type
     *                | Expires
     *                | Last-Modified
     *                | extension-header
     */

    typedef struct {
        char Method[8];      // GET, POST
        char Path[256];      // /index.html
        char Version[16];    // HTTP/1.1
        char Host[128];
        char UserAgent[128];
        char Body[4096];
        int BodyLen;
    } GHttpRequest;

    typedef struct {
        int StatusCode;      // 200, 404
        char StatusMsg[64];  // OK, Not Found
        char Version[16];
        char ContentType[64];
        char Body[8192];
        int BodyLen;
    } GHttpResponse;


    // ========== HTTP 分隔符宏定义 ==========
    #define SP " "           // 空格分隔符 (ASCII 0x20)
    #define SP_CHAR ' '      // 空格字符
    #define CR "\r"          // 回车符 (ASCII 0x0D)
    #define LF "\n"          // 换行符 (ASCII 0x0A)
    #define CRLF "\r\n"      // HTTP 行结束符

}




