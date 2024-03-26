#pragma once
#include "parse_xml.h"
#include <unordered_map>
#include "log.h"
#include "Work.h"
using std::unordered_map;
using namespace Yu::utility;
namespace Yu::plugin
{

    class WorkFlow
    {

            SINGLE(WorkFlow);
    public:
        void load(const string &filename);
        void load_plugin(Work *, Xml &);

        bool run(int id, const string &input, string &output, const string &libname = "");

    private:
        unordered_map<int, Work *> m_work_map;
    };

}