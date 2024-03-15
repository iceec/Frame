#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdexcept>
#include "singleton.h"
#include "Mutex.h"

using namespace std;

namespace Yu
{
  namespace utility
  {
#define loggerpointer single<logger>::instance()

#define LOGGERINFO(format, ...) \
  loggerpointer->savelog(logger::LEVEL_INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGGERDEBUG(format, ...) \
  loggerpointer->savelog(logger::LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGGERERROR(format, ...) \
  loggerpointer->savelog(logger::LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOGGERWARN(format, ...) \
  loggerpointer->savelog(logger::LEVEL_WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)
    class logger
    {

    public:
      enum LEVEL
      {
        LEVEL_DEBUG = 0,
        LEVEL_INFO,
        LEVEL_WARN,
        LEVEL_ERROR,
        LEVEL_FATAL,
        LEVEL_COUNT
      };

      void savelog(LEVEL level, const char *file, int number, const char *format, ...);

      void setlevel(LEVEL level) { logfile_level = level; }

      void open(const string &logfile);

      void close();
      void setconsole();

      void setmaxsize(const size_t x);

      SINGLE(logger)

    private:
      void roate();
      LEVEL logfile_level;

      ofstream logfile_stream;

      string file_name;

      size_t m_len = 0;

      size_t m_maxsize = 0;

      static const char *levelname[LEVEL_COUNT];
      bool is_console;
      Yu::thread::Mutex log_loc;
    };

  }
}
