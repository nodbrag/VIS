#include <fstream>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <time.h>
#include <windows.h>
#include "log.h"
#include "port.h"

//
//  Log critical section (Windows thread synchronization).
//
CRITICAL_SECTION log_critical_section;

//
//  Class constructor for log file object.
//
Log::Log(void)
{
    log_file_name = std::string("log");
}

//
//  Class constructor for log file object using a given file name.
//
Log::Log(const std::string& file_name)
{
    log_file_name = file_name;
    log_date_time_format = std::string("%Y-%m-%d %H:%M:%S");

    InitializeCriticalSection(&log_critical_section);
}

//
//  Copy constructior for log file object using a log object.
//
Log::Log(Log const &log)
{
    log_file_name = std::string(log.log_file_name);
    log_date_time_format = std::string(log.log_date_time_format);

    InitializeCriticalSection(&log_critical_section);
}

//
//  Class destructor for log file object.
//
Log::~Log(void)
{
    DeleteCriticalSection(&log_critical_section);
}

//
//  Set log file name base.
//
void Log::SetFileName(const std::string& file_name)
{
    log_file_name = file_name;
}

//
//  Set date and time format specification.
//
void Log::SetDateTimeFormat(const std::string& date_time_format)
{
    log_date_time_format = std::string(date_time_format);
}

//
//  Write trace log message.
//
void Log::WriteTraceLog(const std::string& trace_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *TRACE: " + trace_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//  Write debug log message.
//
void Log::WriteDebugLog(const std::string& debug_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *DEBUG: " + debug_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//  Write information log message.
//
void Log::WriteInformationLog(const std::string& information_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *INFORMATION: " + information_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//  Write warning log message.
//
void Log::WriteWarningLog(const std::string& warning_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *WARNING: " + warning_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//  Write error log message.
//
void Log::WriteErrorLog(const std::string& error_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *ERROR: " + error_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//   Write fatal log message.
//
void Log::WriteFatalLog(const std::string& fatal_message)
{
    std::string entry = std::string(GetSystemDateTime() + " *FATAL: " + fatal_message + "\n");

    WriteEntryToLogFile(entry);
}

//
//  Write entry to log file.
//
void Log::WriteEntryToLogFile(const std::string& entry)
{
    EnterCriticalSection(&log_critical_section);

    std::string log_fname = std::string(std::string(log_file_name) + "." + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        LeaveCriticalSection(&log_critical_section);
        return;
    }

    log_file << entry;
    log_file.flush();
    log_file.close();

    LeaveCriticalSection(&log_critical_section);
}

//
//  Get current system date only.
//
std::string Log::GetSystemDate()
{
    time_t rawtime;
    struct tm tms;
    char buffer[32];

    Portable::Time(&rawtime);
    Portable::LocalTime(&rawtime, &tms);

    memset(buffer, 0, sizeof(buffer));
    if (Portable::FormatTime(buffer, sizeof(buffer), "%Y-%m-%d", &tms) == EXIT_FAILURE) {
        std::string runtime_error = std::string("error-> Portable::FormatTime() failed: error number(" + std::to_string(errno) + "\n");
        WriteRuntimeErrorToLogFile(runtime_error);
    }

    std::string system_date(buffer);
    return (system_date);
}

//
//  Get current system date and time.
//
std::string Log::GetSystemDateTime()
{
    time_t rawtime;
    struct tm tms;
    char buffer[32];

    Portable::Time(&rawtime);
    Portable::LocalTime(&rawtime, &tms);

    memset(buffer, 0, sizeof(buffer));
    if (Portable::FormatTime(buffer, sizeof(buffer), log_date_time_format.c_str(), &tms) == EXIT_FAILURE) {
        std::string runtime_error = std::string("error-> Portable::FormatTime() failed: error number(" + std::to_string(errno) + ")\n");
        WriteRuntimeErrorToLogFile(runtime_error);
    }

    std::string system_date(buffer);
    return (system_date);
}

//
//  Write runtime error to log file.
//
void Log::WriteRuntimeErrorToLogFile(const std::string& runtime_error)
{
    EnterCriticalSection(&log_critical_section);

    std::string log_fname = std::string(std::string(log_file_name) + std::string(".") + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        LeaveCriticalSection(&log_critical_section);
        return;
    }

    log_file << std::string("0000-00-00 00:00:00 *FATAL: " + runtime_error + "\n");
    log_file.flush();
    log_file.close();

    LeaveCriticalSection(&log_critical_section);
}