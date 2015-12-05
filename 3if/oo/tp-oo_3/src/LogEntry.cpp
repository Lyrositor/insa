#include <stdexcept>

#include "LogEntry.h"

const std::string EXTERNAL_DOCUMENT = "*";

const unsigned char * LogEntry::GetClientIp () const
{
    return clientIp;
}

const std::string & LogEntry::GetLoginName () const
{
    return loginName;
}

const std::string & LogEntry::GetRemoteUser () const
{
    return remoteUser;
}

unsigned short LogEntry::GetDay () const
{
    return day;
}

unsigned short LogEntry::GetMonth () const
{
    return month;
}

unsigned short LogEntry::GetYear () const
{
    return year;
}

unsigned short LogEntry::GetHour () const
{
    return hour;
}

unsigned short LogEntry::GetMinute () const
{
    return minute;
}

unsigned short LogEntry::GetSecond () const
{
    return second;
}

unsigned short LogEntry::GetHourOffset () const
{
    return hourOffset;
}

unsigned short LogEntry::GetMinuteOffset () const
{
    return minuteOffset;
}

const std::string & LogEntry::GetRequestMethod () const
{
    return requestMethod;
}

const std::string & LogEntry::GetRequestUri () const
{
    return requestUri;
}

const std::string LogEntry::GetRequestUriExtension () const
{
    return "png";
}

float LogEntry::GetHttpVersion () const
{
    return httpVersion;
}

unsigned short LogEntry::GetStatusCode () const
{
    return statusCode;
}

unsigned int LogEntry::GetDataSize () const
{
    return dataSize;
}

const std::string & LogEntry::GetRefererUrl () const
{
    return refererUrl;
}

const std::string LogEntry::GetRefererUrlConverted (const std::string & local)
    const
{
    if (local.size() < refererUrl.size() &&
            refererUrl.compare(0, local.size(), local))
    {
        return refererUrl.substr(local.size());
    }
    return EXTERNAL_DOCUMENT;
}

const std::string & LogEntry::GetBrowser () const
{
    return browser;
}

std::istream & operator>> (std::istream & input, LogEntry & logEntry)
{
    throw std::runtime_error("Invalid log entry");
    return input;
}
