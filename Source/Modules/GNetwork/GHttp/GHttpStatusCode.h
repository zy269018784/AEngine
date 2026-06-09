#pragma once

namespace GNetwork
{

        // 1xx: 信息响应
    #define HTTP_CONTINUE                        100  // 继续
    #define HTTP_SWITCHING_PROTOCOLS             101  // 切换协议
    #define HTTP_PROCESSING                      102  // 处理中（WebDAV）
    #define HTTP_EARLY_HINTS                     103  // 早期提示

    // 2xx: 成功
    #define HTTP_OK                              200  // 成功
    #define HTTP_CREATED                         201  // 已创建
    #define HTTP_ACCEPTED                        202  // 已接受
    #define HTTP_NON_AUTHORITATIVE_INFORMATION   203  // 非授权信息
    #define HTTP_NO_CONTENT                      204  // 无内容
    #define HTTP_RESET_CONTENT                   205  // 重置内容
    #define HTTP_PARTIAL_CONTENT                 206  // 部分内容
    #define HTTP_MULTI_STATUS                    207  // 多状态（WebDAV）
    #define HTTP_ALREADY_REPORTED                208  // 已报告（WebDAV）
    #define HTTP_IM_USED                         226  // IM Used

    // 3xx: 重定向
    #define HTTP_MULTIPLE_CHOICES                300  // 多种选择
    #define HTTP_MOVED_PERMANENTLY               301  // 永久移动
    #define HTTP_FOUND                           302  // 临时移动
    #define HTTP_SEE_OTHER                       303  // 查看其他位置
    #define HTTP_NOT_MODIFIED                    304  // 未修改
    #define HTTP_USE_PROXY                       305  // 使用代理
    #define HTTP_TEMPORARY_REDIRECT              307  // 临时重定向
    #define HTTP_PERMANENT_REDIRECT              308  // 永久重定向

    // 4xx: 客户端错误
    #define HTTP_BAD_REQUEST                     400  // 错误请求
    #define HTTP_UNAUTHORIZED                    401  // 未授权
    #define HTTP_PAYMENT_REQUIRED                402  // 需要付款
    #define HTTP_FORBIDDEN                       403  // 禁止访问
    #define HTTP_NOT_FOUND                       404  // 未找到
    #define HTTP_METHOD_NOT_ALLOWED              405  // 方法不允许
    #define HTTP_NOT_ACCEPTABLE                  406  // 不可接受
    #define HTTP_PROXY_AUTHENTICATION_REQUIRED   407  // 需要代理认证
    #define HTTP_REQUEST_TIMEOUT                 408  // 请求超时
    #define HTTP_CONFLICT                        409  // 冲突
    #define HTTP_GONE                            410  // 已消失
    #define HTTP_LENGTH_REQUIRED                 411  // 需要内容长度
    #define HTTP_PRECONDITION_FAILED             412  // 预处理失败
    #define HTTP_PAYLOAD_TOO_LARGE               413  // 负载过大
    #define HTTP_URI_TOO_LONG                    414  // URI过长
    #define HTTP_UNSUPPORTED_MEDIA_TYPE          415  // 不支持的媒体类型
    #define HTTP_RANGE_NOT_SATISFIABLE           416  // 范围不满足
    #define HTTP_EXPECTATION_FAILED              417  // 期望失败
    #define HTTP_IM_A_TEAPOT                     418  // 我是茶壶（愚人节RFC）
    #define HTTP_MISDIRECTED_REQUEST             421  // 错误导向请求
    #define HTTP_UNPROCESSABLE_ENTITY            422  // 不可处理实体（WebDAV）
    #define HTTP_LOCKED                          423  // 已锁定（WebDAV）
    #define HTTP_FAILED_DEPENDENCY               424  // 依赖失败（WebDAV）
    #define HTTP_TOO_EARLY                       425  // 太早
    #define HTTP_UPGRADE_REQUIRED                426  // 需要升级
    #define HTTP_PRECONDITION_REQUIRED           428  // 需要预处理
    #define HTTP_TOO_MANY_REQUESTS               429  // 请求过多
    #define HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE 431  // 请求头字段过大
    #define HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   451  // 因法律原因不可用

    // 5xx: 服务器错误
    #define HTTP_INTERNAL_SERVER_ERROR           500  // 内部服务器错误
    #define HTTP_NOT_IMPLEMENTED                 501  // 未实现
    #define HTTP_BAD_GATEWAY                     502  // 错误网关
    #define HTTP_SERVICE_UNAVAILABLE             503  // 服务不可用
    #define HTTP_GATEWAY_TIMEOUT                 504  // 网关超时
    #define HTTP_VERSION_NOT_SUPPORTED           505  // 版本不支持
    #define HTTP_VARIANT_ALSO_NEGOTIATES         506  // 变体也协商
    #define HTTP_INSUFFICIENT_STORAGE            507  // 存储不足（WebDAV）
    #define HTTP_LOOP_DETECTED                   508  // 检测到循环（WebDAV）
    #define HTTP_NOT_EXTENDED                    510  // 未扩展
    #define HTTP_NETWORK_AUTHENTICATION_REQUIRED 511  // 需要网络认证

    #define STATUS_TEXT_200 "OK"
    #define STATUS_TEXT_201 "Created"
    #define STATUS_TEXT_202 "Accepted"
    #define STATUS_TEXT_204 "No Content"
    #define STATUS_TEXT_301 "Moved Permanently"
    #define STATUS_TEXT_302 "Found"
    #define STATUS_TEXT_304 "Not Modified"
    #define STATUS_TEXT_400 "Bad Request"
    #define STATUS_TEXT_401 "Unauthorized"
    #define STATUS_TEXT_403 "Forbidden"
    #define STATUS_TEXT_404 "Not Found"
    #define STATUS_TEXT_405 "Method Not Allowed"
    #define STATUS_TEXT_408 "Request Timeout"
    #define STATUS_TEXT_409 "Conflict"
    #define STATUS_TEXT_410 "Gone"
    #define STATUS_TEXT_413 "Payload Too Large"
    #define STATUS_TEXT_414 "URI Too Long"
    #define STATUS_TEXT_415 "Unsupported Media Type"
    #define STATUS_TEXT_418 "I'm a teapot"
    #define STATUS_TEXT_429 "Too Many Requests"
    #define STATUS_TEXT_431 "Request Header Fields Too Large"
    #define STATUS_TEXT_451 "Unavailable For Legal Reasons"
    #define STATUS_TEXT_500 "Internal Server Error"
    #define STATUS_TEXT_501 "Not Implemented"
    #define STATUS_TEXT_502 "Bad Gateway"
    #define STATUS_TEXT_503 "Service Unavailable"
    #define STATUS_TEXT_504 "Gateway Timeout"
    #define STATUS_TEXT_505 "HTTP Version Not Supported"
}