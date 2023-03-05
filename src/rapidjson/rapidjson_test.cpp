#include "../header.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include <fstream>
#include <ostream>
#include <rapidjson/filereadstream.h>

using namespace rapidjson;

TEST(JsonTest, test001)
{
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    LOG(INFO) << buffer.GetString() << std::endl;
}

TEST(JsonTest, test002)
{
    FILE* fp = fopen("test.json", "r"); // stupid windows need rb
    char buf[0XFFFF];

    //FileReadStream(FILE *fp, char *buffer, std::size_t bufferSize)
    rapidjson::FileReadStream input(fp, buf, sizeof(buf));
    rapidjson::Document document;
    document.ParseStream(input);
    fclose(fp);

    cout << boolalpha;
    cout << document["servertype"]["value"].GetString() << endl;

}