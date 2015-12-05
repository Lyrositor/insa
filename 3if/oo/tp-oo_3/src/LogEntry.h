#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <iostream>
#include <string>

class LogEntry
{
public:
    const unsigned char * GetClientIp () const;
    const std::string & GetLoginName () const;
    const std::string & GetRemoteUser () const;
    unsigned short GetDay () const;
    unsigned short GetMonth () const;
    unsigned short GetYear () const;
    unsigned short GetHour () const;
    unsigned short GetMinute () const;
    unsigned short GetSecond () const;
    unsigned short GetHourOffset () const;
    unsigned short GetMinuteOffset () const;
    const std::string & GetRequestMethod () const;
    const std::string & GetRequestUri () const;
    const std::string GetRequestUriExtension () const;
    float GetHttpVersion () const;
    unsigned short GetStatusCode () const;
    unsigned int GetDataSize () const;
    const std::string & GetRefererUrl () const;
    const std::string GetRefererUrlConverted (const std::string & local)
            const;
    const std::string & GetBrowser () const;

    friend std::istream &operator>> (std::istream & input, LogEntry & logEntry);

protected:
    unsigned char clientIp[4];
    std::string loginName, remoteUser;
    unsigned short day, month, year, hour, minute, second, hourOffset,
            minuteOffset;
    std::string requestMethod, requestUri;
    float httpVersion;
    unsigned short statusCode;
    unsigned int dataSize;
    std::string refererUrl, browser;
};


#endif // LOG_ENTRY_H
