#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <iostream>
#include <regex>
#include <set>
#include <string>

class LogEntry
{
public:
    const unsigned char * GetClientIp () const;
    const std::string & GetLoginName () const;
    const std::string & GetRemoteUser () const;
    unsigned short GetDay () const;
    const std::string & GetMonth () const;
    unsigned short GetYear () const;
    unsigned short GetHour () const;
    unsigned short GetMinute () const;
    unsigned short GetSecond () const;
    unsigned short GetHourOffset () const;
    unsigned short GetMinuteOffset () const;
    const std::string & GetRequestMethod () const;
    const std::string & GetRequestUri () const;
    const std::string GetRequestUriConverted () const;
    const std::string GetRequestUriExtension () const;
    double GetHttpVersion () const;
    unsigned short GetStatusCode () const;
    int GetDataSize () const;
    const std::string & GetRefererUrl () const;
    const std::string GetRefererUrlConverted (const std::string & local)
            const;
    const std::string & GetBrowser () const;

    friend std::istream &operator>> (std::istream & input, LogEntry & logEntry);

protected:
    static const std::string EXTERNAL_DOCUMENT;

    static const std::regex APACHE_LOG_ENTRY;
    static const std::regex REQUEST_URI;

    unsigned char clientIp[4];
    std::string loginName, remoteUser;
    unsigned short day;
    std::string month;
    unsigned short year, hour, minute, second, hourOffset, minuteOffset;
    std::string requestMethod, requestUri;
    double httpVersion;
    unsigned short statusCode;
    int dataSize;
    std::string refererUrl, browser;

    bool parseUri(const std::string & uri, std::smatch & match) const;
};


#endif // LOG_ENTRY_H
