#include <vector>

class string
{
    char* str;
    int len;

public:
    string(char c, int n); // 문자 c 가 n 개 있는 문자열로 정의
    string(const char* s);
    string(const string& s);
    ~string();

    void add_string(const string& s);  // str 뒤에 s 를 붙인다.
    void copy_string(const string& s); // str 에 s 를 복사한다.
    int strlen() const;                // 문자열 길이 리턴
};

string::string(char c, int n)
{
    str = new char[n];
    for (int i = 0; i < n; ++i) {
        str[i] = c;
    }
    len = n;
}

string::string(const char* s)
{
    int cnt = 0;
    while (s[cnt] != '\0') {
        ++cnt;
    }

    str = new char[cnt];
    for (int i = 0; i < cnt; ++i) {
        str[i] = s[i];
    }
    len = cnt;
}

string::string(const string& s)
{
    str = new char[s.strlen()];
    copy_string(s);
}

string::~string()
{
    if (str) {
        delete[] str;
    }
}

void string::add_string(const string& s)
{
    char* s_str = s.str;
    int s_len = s.strlen();

    char* temp = new char[len + s_len];

    int offset = len;
    for (int i = 0; i < len; ++i) {
        temp[i] = str[i];
    }
    for (int i = 0; i < s_len; ++i) {
        temp[i + offset] = s_str[i];
    }

    delete[] str;
    str = temp;
    len = s_len + len;
}

void string::copy_string(const string& s)
{
    char* s_str = s.str;
    int s_len = s.strlen();

    if (s_len != len) {
        delete[] str;
        str = new char[s_len];
    }

    for (int i = 0; i < s_len; ++i) {
        str[i] = s_str[i];
    }

    len = s_len;
}

int string::strlen() const
{
    return len;
}
