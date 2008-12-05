// Author: Hong Jiang <hong@hjiang.net>

#include <cassert>
#include <sstream>
#include <string>

#include "jsonxx.h"

namespace jsonxx {
bool parse_string(std::istream& input, std::string* value);
bool parse_number(std::istream& input, long* value);
bool match(const std::string& pattern, std::istream& input, bool ignore_ws = true);
}

int main() {
    using namespace jsonxx;
    using namespace std;
    {
        string teststr("\"field1\"");
        string value;
        istringstream input(teststr);
        assert(parse_string(input, &value));
    }
    {
        string teststr("\"  field1\"");
        string value;
        istringstream input(teststr);
        assert(parse_string(input, &value));
    }
    {
        string teststr("  \"field1\"");
        string value;
        istringstream input(teststr);
        assert(parse_string(input, &value));
    }
    {
        string teststr("6");
        istringstream input(teststr);
        long value;
        assert(parse_number(input, &value));
    }
    {
        string teststr(" }");
        istringstream input(teststr);
        assert(match("}", input));
    }
    {
        string teststr("{ \"field1\" : 6 }");
        istringstream input(teststr);
        Object o;
        assert(o.parse(input));
    }
    {
        string teststr("{ \"field1 : 6 }");
        istringstream input(teststr);
        Object o;
        assert(!o.parse(input));
    }
    {
        string teststr("6");
        istringstream input(teststr);
        Value v;
        assert(v.parse(input));
    }
    {
        string teststr("asdf");
        istringstream input(teststr);
        Value v;
        assert(!v.parse(input));
    }
    {
        string teststr("true");
        istringstream input(teststr);
        Value v;
        assert(v.parse(input));
        assert(v.is<bool>());
    }
    {
        string teststr("false");
        istringstream input(teststr);
        Value v;
        assert(v.parse(input));
        assert(v.is<bool>());
        assert(v.get<bool>() == false);
    }
    {
        string teststr("null");
        istringstream input(teststr);
        Value v;
        assert(v.parse(input));
        assert(v.is<Value::Null>());
        assert(!v.is<bool>());
    }
    {
        string teststr("\"field1\"");
        istringstream input(teststr);
        Value v;
        assert(v.parse(input));
        assert(v.is<std::string>());
        assert("field1" == v.get<std::string>());
    }
    {
        string teststr("[\"field1\", 6]");
        istringstream input(teststr);
        Array v;
        assert(v.parse(input));
    }
}
