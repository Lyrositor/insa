#include <stdexcept>

#include "LogEntry.h"


const std::string LogEntry::EXTERNAL_DOCUMENT = "*";

const std::regex LogEntry::REQUEST_URI(
        R"(^(?:\:\d+)?((?:\/(?:[^\/?]+\/)*)?([^.\/?][^\/?]+?)?(?:\.(\w*))?))"
        R"((?:[\?;].*)?$)"
);
const std::regex LogEntry::APACHE_LOG_ENTRY(
        R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}) (\S+) (\S+) )"
        R"(\[(\d{2})\/(\w{3})\/(\d{4})\:(\d{2})\:(\d{2})\:(\d{2}) )"
        R"(\+(\d{2})(\d{2})] \"([A-Z]+) ([^\"]*?)\s+HTTP\/(\d\.\d)\" (\d+) )"
        R"((\d+|\-) \"([^\"]*)\" \"([^\"]*)\"$)"
);

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

const std::string & LogEntry::GetMonth () const
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

const std::string LogEntry::GetRequestUriConverted () const
{
    std::smatch match;
    if (!parseUri(requestUri, match))
    {
        return requestUri;
    }
    return match[1];
}

const std::string LogEntry::GetRequestUriExtension () const
{
    std::smatch match;
    if (!parseUri(requestUri, match))
    {
        return "";
    }
    return match[3];
}

double LogEntry::GetHttpVersion () const
{
    return httpVersion;
}

unsigned short LogEntry::GetStatusCode () const
{
    return statusCode;
}

int LogEntry::GetDataSize () const
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
    if (!refererUrl.compare(0, local.size(), local))
    {
        std::string convertedUrl = refererUrl.substr(local.size());
        std::smatch match;
        if (!parseUri(convertedUrl, match))
        {
            return convertedUrl;
        }
        return match[1];
    }
    return EXTERNAL_DOCUMENT;
}

const std::string & LogEntry::GetBrowser () const
{
    return browser;
}

std::istream & operator>> (std::istream & input, LogEntry & logEntry)
{
    std::string line;
    std::getline(input, line);
    if (line.empty())
    {
        return input;
    }
    std::smatch match;
    if (!std::regex_match(line, match, LogEntry::APACHE_LOG_ENTRY))
    {
        throw std::runtime_error("Invalid log entry");
    }
    logEntry.clientIp[0] = atoi(match[1].str().c_str());
    logEntry.clientIp[1] = atoi(match[2].str().c_str());
    logEntry.clientIp[2] = atoi(match[3].str().c_str());
    logEntry.clientIp[3] = atoi(match[4].str().c_str());
    logEntry.loginName = match[5];
    logEntry.remoteUser = match[6];
    logEntry.day = atoi(match[7].str().c_str());
    logEntry.month = match[8];
    logEntry.year = atoi(match[9].str().c_str());
    logEntry.hour = atoi(match[10].str().c_str());
    logEntry.minute = atoi(match[11].str().c_str());
    logEntry.second = atoi(match[12].str().c_str());
    logEntry.hourOffset = atoi(match[13].str().c_str());
    logEntry.minuteOffset = atoi(match[14].str().c_str());
    logEntry.requestMethod = match[15];
    logEntry.requestUri = match[16];
    logEntry.httpVersion = atof(match[17].str().c_str());
    logEntry.statusCode = atoi(match[18].str().c_str());
    logEntry.dataSize = atoi(match[19].str().c_str());
    logEntry.refererUrl = match[20];
    logEntry.browser = match[21];
    return input;
}

bool LogEntry::parseUri (const std::string & uri, std::smatch & match) const
{
    return std::regex_match(uri, match, REQUEST_URI);
}
