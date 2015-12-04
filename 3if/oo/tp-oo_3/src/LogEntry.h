#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <iostream>

class LogEntry
{
public:
    const char * getClientIp () const;
    const std::string & getLoginName () const;
    const std::string & getRemoteUser () const;
    short getDay () const;
    short getMonth () const;
    short getYear () const;
    short getHour () const;
    short getMinute () const;
    short getSecond () const;
    short getHourOffset () const;
    short getMinuteOffset () const;
    const std::string & getRequestMethod () const;
    const std::string & getRequestUri () const;
    float getHttpVersion () const;
    short getStatusCode () const;
    int getDataSize () const;
    const std::string & getRefererUrl () const;
    const std::string & getBrowser () const;

    friend std::istream &operator>> (std::istream & input, LogEntry & logEntry);

protected:
    char clientIp[4];
    std::string loginName, remoteUser;
    short day, month, year, hour, minute, second, hourOffset, minuteOffset;
    std::string requestMethod, requestUri;
    float httpVersion;
    short statusCode;
    int dataSize;
    std::string refererUrl, browser;
};


#endif //I LOG_ENTRY_H
