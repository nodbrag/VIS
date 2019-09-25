#ifndef __LOG_H
#define __LOG_H

#include <windows.h>
#include <string>

//
//  Log class.
//
class Log {
public:
        Log(void);
        Log(const std::string& file_name);
        Log(Log const&);
       ~Log(void);
        void SetFileName(const std::string&);
        void SetDateTimeFormat(const std::string&);
        void WriteTraceLog(const std::string&);
        void WriteDebugLog(const std::string&);
        void WriteInformationLog(const std::string&);
        void WriteWarningLog(const std::string&);
        void WriteErrorLog(const std::string&);
        void WriteFatalLog(const std::string&);

private:
        void WriteEntryToLogFile(const std::string&);
        std::string GetSystemDate();
        std::string GetSystemDateTime();
        void WriteRuntimeErrorToLogFile(const std::string&);

private:
        std::string log_file_name;
        std::string log_date_time_format;
        CRITICAL_SECTION log_critical_section;
};

#endif // __LOG_H
