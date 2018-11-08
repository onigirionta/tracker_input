#include "parser.h"

using namespace std;

int
main() {
    auto v1 =
            parse_line("{\"ts\":3400,\"rt\":{\"s\":133,\"A\":\"0x100\",\"B\":\"0x204\",\"ddist_mm\":4254,\"B_euid\":\"0x10205fe110001dd7\"},\"B_baro_cm\":24455}");
    assert ((v1 == std::vector<double>{
            1,
            3400,
            133,
            4,
            4254,
            24455}));

    auto v2 = parse_line("{\"ts\":3404,\"a\":[1997,-504,89],\"g\":[-17,-3,4],"
                      "\"q\":[255593053,-754998296,-79182262,-715053453],"
                      "\"m\":[-4,269,-368],\"t\":0,\"p\":98428}");
    assert((v2 == std::vector<double>{
            2,
            3404,
            1997, -504, 89,
            -17, -3, 4,
            255593053, -754998296, -79182262, -715053453,
            -4, 269, -368,
            0,
            98428}));

    auto v3 =
            parse_line("{\"ts\":3437,\"rt\":{\"s\":135,\"A\":\"0x100\",\"A_euid\":\"0x10205fe110001d4e\"},\"A_baro_cm\":24740}");
    assert ((v3 == std::vector<double>{
            3,
            3437,
            135}));

    try {
        auto v4 = parse_line("");
        assert(!"exception expected");
    }
    catch (...) {}

    istringstream in5{
            "{\"ts\":3400,\"rt\":{\"s\":133,\"A\":\"0x100\",\"B\":\"0x204\","
            "\"ddist_mm\":4254,\"B_euid\":\"0x10205fe110001dd7\"},\"B_baro_cm\":24455}\n"

            "{\"ts\":3404,\"a\":[1997,-504,89],\"g\":[-17,-3,4],"
            "\"q\":[255593053,-754998296,-79182262,-715053453],"
            "\"m\":[-4,269,-368],\"t\":0,\"p\":98428}\n"

            "{\"ts\":3437,\"rt\":{\"s\":135,\"A\":\"0x100\","
            "\"A_euid\":\"0x10205fe110001d4e\"},\"A_baro_cm\":24740}"
    };
    auto v5 = go(in5);
    assert((v5 == vector<vector<double>>{
            {
                    1,
                    3400,
                    133,
                          4,
                                4254,
                    24455},
            {
                    2,
                    3404,
                    1997, -504, 89,
                    -17, -3, 4,
                    255593053, -754998296, -79182262, -715053453,
                    -4, 269, -368,
                    0,
                    98428},
            {
                    3,
                    3437,
                    135}
    }));
}