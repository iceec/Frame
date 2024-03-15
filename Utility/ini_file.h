#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include "value.h"
#include "singleton.h"
using namespace std;

namespace Yu
{

    namespace utility
    {
        class ini
        {

            typedef unordered_map<string, value> section;
            SINGLE(ini);

        public:
            void load(const string &f);
            void show() const;

            value &get(const string &section, const string &key);

            bool set(const string &section, const string &key, const value &val);
            section &operator[](const string &section);
            string str() const;
            bool has(const string &section) const;
            bool has(const string &section, const string &key);

            void remove(const string &section);
            void remove(const string &section, const string &key);

        private:
            // typedef unordered_map<string,value> section;
            unordered_map<string, section> ini_file;
            string file_name;
            string trim(string line, string f);
        };

    }

}