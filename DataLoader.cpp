#include "DataLoader.h"

// 读取文件
void getvertex(std::string& s, vertex_position& v) {
    int i(0), j(0), k(0);
    for (; i < s.size() && s[i] != ' '; i++);
    std::istringstream iss1(s.substr(0, i));
    iss1 >> v.x; v.x *= 1000;
    for (j = i + 1; j < s.size() && s[j] != ' '; j++);
    std::istringstream iss2(s.substr(i + 1, j - i - 1));
    iss2 >> v.y; v.y *= 1000;
    for (k = j + 1; k < s.size() && s[k] != ' '; k++);
    std::istringstream iss3(s.substr(j + 1, k - j - 1));
    iss3 >> v.z; v.z *= 1000;
}

void getsurfaceidx(std::string& s, Indexbuffer& dx) {
    int i(0), j(0), k(0);
    for (i = 2; i < s.size() && s[i] != ' '; i++);
    dx.a = stoi(s.substr(2, i - 2));
    for (j = i + 1; j < s.size() && s[j] != ' '; j++);
    dx.b = stoi(s.substr(i + 1, j - i - 1));
    for (k = j + 1; k < s.size() && s[k] != ' '; k++);
    dx.c = stoi(s.substr(j + 1, k - j - 1));
}

void Loader() {
    std::ifstream file("bunny.ply");

    std::string buffer;

    int b(0); // 取0阅读头部，取1阅读vertex，取2阅读surface
    int readn(0);

    while (!file.eof()) {
        std::getline(file, buffer);
        switch (b)
        {
        case 0:
        {
            if (buffer.substr(0, 14) == std::string("element vertex"))
                VNUM = stoi(buffer.substr(15, buffer.size() - 15));
            else if (buffer.substr(0, 12) == std::string("element face"))
                SNUM = stoi(buffer.substr(13, buffer.size() - 13));
            else if (buffer == std::string("end_header"))
                b = 1;
            break;
        }
        case 1:
        {
            getvertex(buffer, VertexBuffer[readn++]);
            if (readn == VNUM)
                b = 2, readn = 0;
            break;
        }
        case 2:
        {
            getsurfaceidx(buffer, IndexBuffer[readn++]);
            if (readn == SNUM)
                b = 3, readn = 0;
            break;
        }
        default:
            break;
        }
    }
}