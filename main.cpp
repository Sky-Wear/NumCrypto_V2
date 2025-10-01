#include <iostream>
#include <string>
#include <random>
#include <algorithm>
std::string padStart(const std::string &str, size_t num, char ch) {
    std::string result = str;
    if (num > str.size()) {
        result.insert(0, num - str.size(), ch);
    }
    return result;
}
std::string a(std::string str) {
    int i = std::stoi(str.substr(0, 2));
    int i2 = std::stoi(str.substr(2, 2));
    int i3 = std::stoi(str.substr(4, 2));
    int i4 = std::stoi(str.substr(6, 2));
    int i5 = std::stoi(str.substr(8));

    int i6 = i4 ^ i3;
    int i7 = i5 ^ i3;
    int i8 = i3 ^ (i6 + i7);
    int i9 = i ^ i7;
    int i10 = i2 ^ i7;
    return padStart(std::to_string(i9), 2, '0') +
        padStart(std::to_string(i10), 2, '0') +
        padStart(std::to_string(i6), 2, '0') +
        padStart(std::to_string(i7), 2, '0') +
        padStart(std::to_string(i8), 2, '0');
}
std::string b(std::string str) {
    int i = std::stoi(str.substr(0, 2));
    int i2 = std::stoi(str.substr(2, 2));
    int i3 = std::stoi(str.substr(4, 2));
    int i4 = std::stoi(str.substr(6, 2));
    int i5 = std::stoi(str.substr(8));

    int i6 = i5 ^ (i3 + i4);
    int i7 = i4 ^ i6;
    int i8 = i3 ^ i6;
    int i9 = i ^ i6;
    int i10 = i2 ^ i6;
    return padStart(std::to_string(i9), 2, '0') +
        padStart(std::to_string(i10), 2, '0') +
        padStart(std::to_string(i8), 2, '0') +
        padStart(std::to_string(i7), 2, '0') +
        padStart(std::to_string(i6), 2, '0');
}

std::string c(std::string str) {
    int i = std::stoi(str.substr(0, 2));
    int i2 = std::stoi(str.substr(2, 2));
    int i3 = std::stoi(str.substr(4));

    int i5 = i3 ^ (i + i2);
    int i6 = i ^ i5;
    int i4 = i2 ^ i5;

    return padStart(std::to_string(i6), 2, '0') +
        padStart(std::to_string(i4), 2, '0') +
        padStart(std::to_string(i5), 2, '0');
}

std::string d(const std::string &str) {
    int i = std::stoi(str.substr(0, 2));
    int i2 = std::stoi(str.substr(2, 2));
    int i3 = std::stoi(str.substr(4));

    int i5 = i2 ^ i;
    int i6 = i3 ^ i;
    int i4 = i ^ (i5 + i6);

    return padStart(std::to_string(i5), 2, '0') +
        padStart(std::to_string(i6), 2, '0') +
        padStart(std::to_string(i4), 2, '0');
}

void middle(std::string str, char fill) {
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    int dwSizeX = bInfo.dwSize.X, dwSizey = bInfo.dwSize.Y;
    int len = str.length();
    int x = dwSizeX / 2 - len / 2;
    for (int i = 0; i < x; i++) {
        std::cout << fill;
    }

    std::cout << str;
    for (int i = x + len; i < dwSizeX; i++) {
        std::cout << fill;
    }
    std::cout << std::endl;
}
struct MemoryStruct {
  char *memory;
  size_t size;
  MemoryStruct() {
      memory = (char *) malloc(1);
      size = 0;
  }
  ~MemoryStruct() {
      free(memory);
      memory = nullptr;
      size = 0;
  }
};

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) data;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

namespace newCode {

bool isNumeric(const std::string &str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::string encode(const std::string &str, int type) {
    if (str.empty() || !isNumeric(str) || str.length() != 7 || (type != 1 && type != 2)) {
        return "";
    } else {
        std::string result = "";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 6);
        int keyId = dis(gen);

        int intArr[7];
        for (int i = 0; i < 7; ++i) {
            intArr[i] = str[i] - '0';
        }
        int key = intArr[keyId];
        for (int i = 0; i < 7; ++i) {
            int curKey = (i == keyId) ? keyId : key;
            int curInt = intArr[i];
            result += std::to_string((curInt + curKey) % 10);
        }
        result += std::to_string(type ^ keyId);
        return result;
    }
}

std::string decode(const std::string &str, int type) {
    if (str.empty() || !isNumeric(str) || str.length() != 8 || (type != 1 && type != 2)) {
        return "";
    } else {
        std::string result = "";
        int intArr[8];
        for (int i = 0; i < 8; ++i) {
            intArr[i] = str[i] - '0';
        }
        int key = intArr[7] ^ type;
        int v7 = (intArr[key] - key + 10) % 10;
        for (int i = 0; i <= 6; ++i) {
            int curKey = v7;
            if (i == key) {
                result += std::to_string(v7);
                continue;
            }
            int curInt = intArr[i];
            result += std::to_string((curInt + 10 - curKey) % 10);
        }
        return result;
    }
}
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    if(true){

        int mode;
        middle("NumCrypto 2.0", '=');
        std::cout << "请输入模式:(1:ADB(旧) 2:自检(旧) 3:ADB(新) 4:自检(新))";
        std::cin >> mode;

        if (mode == 1) {
            middle("ADB", '=');
            std::cout << "输入设备码:";
            std::string s;
            std::cin >> s;
            middle("结果", ' ');
            middle(a(b(s)), ' ');
        } else if (mode == 2) {
            middle("自检", '=');
            std::cout << "输入设备码:";
            std::string s;
            std::cin >> s;
            std::string R1 = c(s);
            middle("结果", ' ');
            middle(d(R1), ' ');
        } else if (mode == 3) {
            middle("ADB(新)", '=');
            std::cout << "输入设备码:";
            std::string s;
            std::cin >> s;
            middle("结果", ' ');
            middle(newCode::encode(newCode::decode(s, 2), 2), ' ');
        } else if (mode == 4) {
            middle("自检(新)", '=');
            std::cout << "输入设备码:";
            std::string s;
            std::cin >> s;
            std::string R1 = c(s);
            middle("结果", ' ');
            middle(newCode::encode(newCode::decode(s, 1), 1), ' ');
        }
        system("pause");
    } else {
        std::cout << "加载失败！";
        system("pause");
    }
    return 0;
}
