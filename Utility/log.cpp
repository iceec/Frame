#include "log.h"

#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <cstdarg>

using namespace std;
// 命名空间和常规一样 就是为了不重复，没什么全部都便在一起
namespace Yu
{
    namespace utility
    {

        const char *logger::levelname[LEVEL_COUNT] = {
            "Debug: ", "Info: ", "Warn: ", "Error: ", "Fatal: "};

        void logger::open(const string &logfile)
        {

            logfile_stream.open(logfile, std::ios::app);

            if (logfile_stream.fail())
                throw logic_error("can't open this log file" + logfile);
            file_name = logfile;
            cout << file_name << endl;
            m_len = 0;
        }

        logger::logger() : logfile_level(LEVEL_DEBUG), m_len(0), m_maxsize(0), is_console(true), log_loc() {}

        void logger::close()
        {
            logfile_stream.close();
            m_len = 0;
        }
        void logger::setconsole()
        {
            is_console = false;
        }

        void logger::setmaxsize(const size_t x)
        {
            m_maxsize = x;
        }

        logger::~logger()
        {
            close();
        }

        void logger::savelog(LEVEL level, const char *file, int number, const char *format, ...)
        {
            if (logfile_level > level)
                return;

            time_t ticks = time(nullptr);

            tm *local = localtime(&ticks);

            local->tm_year += 1900;

            local->tm_mon += 1;

            ostringstream ss;

            ss << levelname[level];
            //<< local->tm_year << "-" << local->tm_mon << "-" << local->tm_mday << " "
            // 存时间
            ss << local->tm_hour << ":"
               << local->tm_min << ":" << local->tm_sec << "  " << file << ": " << number << "  ";

            va_list va;

            va_start(va, format);

            size_t len = vsnprintf(nullptr, 0, format, va);
            va_end(va);

            if (len > 0)
            {
                va_start(va, format);
                char buffer[len + 1];
                vsnprintf(buffer, len, format, va);
                va_end(va);
                buffer[len] = 0;
                ss << buffer;
            }

            const string &p = ss.str();
            log_loc.lock();
            logfile_stream << p.c_str() << endl;
            logfile_stream.flush();
            log_loc.unlock();

            if (is_console)
                printf("%s\n", p.c_str());

            m_len += ss.str().size();

            if (m_maxsize > 0 && m_len > m_maxsize)
            {
                close();
                roate();
            }

            return;
        }

        void logger::roate()
        {

            sleep(1000);

            time_t ticks = time(nullptr);

            tm *local = localtime(&ticks);

            local->tm_year += 1900;

            local->tm_mon += 1;

            ostringstream ss;

            // 存时间
            ss << local->tm_year << "_" << local->tm_mon << "_" << local->tm_mday << "_" << local->tm_hour << "_"
               << local->tm_min << "_" << local->tm_sec;

            string newfile = ss.str() + file_name;

            if (rename(file_name.c_str(), newfile.c_str()) != 0)
                cout << newfile << endl;

            open(file_name);

            return;
        }

    }
}
