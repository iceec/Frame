#pragma once
#include <typeinfo>
#include <string>
#include <unordered_map>
#include "singleton.h"
#include <stdexcept>
using std::string;
using std::unordered_map;

namespace Yu::utility
{

    class Object
    {
    public:
        Object() = default;
        virtual ~Object() {}
    };

    class Context
    {
        SINGLE(Context);

    public:
        void clear();
        template <class T>
        void set(const string &key, T value);
        inline void set(const string &key, const string &value);
        inline void set(const string &key, const char *value);
        inline void set(const string &key, Object *value);
        template <class T>
        bool get(const string &key, T &);
        inline bool get(const string &key, Object *(& p));
        inline bool get(const string &key, string &p);
        bool get(const string &key, char *buf, int len);

    private:
        unordered_map<string, bool> m_bool;
        unordered_map<string, char> m_char;
        unordered_map<string, int> m_int;
        unordered_map<string, double> m_double;
        unordered_map<string, string> m_string;
        unordered_map<string, Object *> m_objs;
    };

    template <class T>
    void Context::set(const string &key, T value)
    {

        if (typeid(T) == typeid(bool))
            m_bool[key] = value;
        else if (typeid(T) == typeid(int))
            m_int[key] = value;
        else if (typeid(T) == typeid(char))
            m_char[key] = value;
        else if (typeid(T) == typeid(double))
            m_double[key] = value;
        else
            throw std::logic_error("no set");
    }

    void Context::set(const string &key, const string &value)
    {
        m_string[key] = value;
    }

    void Context::set(const string &key, const char *value)
    {
        m_string[key] = value;
    }

    void Context::set(const string &key, Object *value)
    {
        m_objs[key] = value;
    }

    template <class T>
    bool Context::get(const string &key, T &p)
    {
        if (typeid(T) == typeid(bool))
        {
            if (m_bool.count(key))
                p = m_bool[key];
            else
                return false;
        }
        else if (typeid(T) == typeid(int))
        {
            if (m_int.count(key))
                p = m_int[key];
            else
                return false;
        }
        else if (typeid(T) == typeid(char))
        {
            if (m_char.count(key))
                p = m_char[key];
            else
                return false;
        }
        else if (typeid(T) == typeid(double))
        {
            if (m_double.count(key))
                p = m_double[key];
            else
                return false;
        }
        else
            throw std::logic_error("no get");

        return true;
    }

  
    bool Context::get(const string &key, string &p)
    {
        if (m_string.count(key))
            p = m_string[key];
        else
            return false;

        return true;
    }

    bool Context::get(const string &key, Object *(& p))
    {
        if (m_objs.count(key))
            p = m_objs[key];
        else
            return false;
        return true;
    }

}

//quesetion  为什么有的作片特化不可以呢  