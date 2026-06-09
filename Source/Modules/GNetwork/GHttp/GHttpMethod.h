#pragma once

namespace GHttp
{
    // ========== HTTP 请求方法宏定义（RFC 7231）==========

    /*
     * Http 0.9
     */
    #define METHOD_GET     "GET"       // 获取资源
    /*
     * Http 1.0
     */
    #define METHOD_HEAD    "HEAD"      // 获取响应头
    #define METHOD_POST    "POST"      // 提交数据
    #define METHOD_PUT     "PUT"       // 替换资源
    /*
    * Http 1.1
    */
    #define METHOD_PATCH   "PATCH"     // 部分修改资源
    #define METHOD_OPTIONS "OPTIONS"   // 查询支持的方法
    #define METHOD_DELETE  "DELETE"    // 删除资源
    #define METHOD_CONNECT "CONNECT"   // 建立隧道
    #define METHOD_TRACE   "TRACE"     // 回显请求
    /*
     * WebDAV 方法（RFC 4918）
     */
    #define METHOD_PROPFIND   "PROPFIND"    // 获取属性
    #define METHOD_PROPPATCH  "PROPPATCH"   // 修改属性
    #define METHOD_MKCOL      "MKCOL"       // 创建集合
    #define METHOD_COPY       "COPY"        // 复制资源
    #define METHOD_MOVE       "MOVE"        // 移动资源
    #define METHOD_LOCK       "LOCK"        // 锁定资源
    #define METHOD_UNLOCK     "UNLOCK"      // 解锁资源
    /*
     * 其他扩展方法
     */
    #define METHOD_PURGE    "PURGE"     // 清除缓存（Squid/Varnish）
    #define METHOD_LINK     "LINK"      // 建立链接
    #define METHOD_UNLINK   "UNLINK"    // 断开链接
}










