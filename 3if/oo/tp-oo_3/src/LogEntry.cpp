#include "LogEntry.h"

const char * LogEntry::getClientIp () const
{
    return clientIp;
}

const std::string & LogEntry::getLoginName () const
{
    return loginName;
}

const std::string & LogEntry::getRemoteUser () const
{
    return remoteUser;
}

short LogEntry::getDay () const
{
    return day;
}

short LogEntry::getMonth () const
{
    return month;
}

short LogEntry::getYear () const
{
    return year;
}

short LogEntry::getHour () const
{
    return hour;
}

short LogEntry::getMinute () const
{
    return minute;
}

short LogEntry::getSecond () const
{
    return second;
}

short LogEntry::getHourOffset () const
{
    return hourOffset;
}

short LogEntry::getMinuteOffset () const
{
    return minuteOffset;
}

const std::string & LogEntry::getRequestMethod () const
{
    return requestMethod;
}

const std::string & LogEntry::getRequestUri () const
{
    return requestUri;
}

float LogEntry::getHttpVersion () const
{
    return httpVersion;
}

short LogEntry::getStatusCode () const
{
    return statusCode;
}

int LogEntry::getDataSize () const
{
    return dataSize;
}

const std::string & LogEntry::getRefererUrl () const
{
    return refererUrl;
}

const std::string & LogEntry::getBrowser () const
{
    return browser;
}

std::istream & operator>> (std::istream & input, LogEntry & logEntry)
{
    return input;
}
