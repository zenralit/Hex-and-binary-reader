#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <bitset>
#include <windows.h>
#include <sstream>
#include <stdexcept>
#include <algorithm> 
#include <cctype>   
using namespace std;
string byteToBinary(unsigned char byte) {
    return bitset<8>(byte).to_string();
}
void editFile(const string& filename, size_t position, unsigned char newValue) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        throw runtime_error("не получается изменить файл");
    }

    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();

    if (position >= fileSize) {
        file.seekp(position);
        char zero = 0;
        file.write(&zero, 1);
    }

    file.seekp(position);
    file.write(reinterpret_cast<const char*>(&newValue), 1);

    if (!file.good()) {
        throw runtime_error("ошибка");
    }
}
void printHexDump(const string& filename, int page = 0, int pageSize = 256, bool showBinary = false) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "ошибка открытия" << endl;
        return;
    }

    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    size_t startPos = page * pageSize;
    startPos = min(startPos, fileSize);

    file.seekg(startPos);
    char buffer[16];
    size_t bytesRead;

    for (size_t i = 0; i < pageSize / 16; ++i) {
        size_t currentPos = startPos + i * 16;
        file.read(buffer, 16);
        bytesRead = file.gcount();
        if (bytesRead == 0) break;

        cout << hex << setw(8) << setfill('0') << currentPos << "  ";

        for (size_t j = 0; j < 16; ++j) {
            if (j < bytesRead) {
                cout << hex << setw(2) << setfill('0')
                    << static_cast<int>(static_cast<unsigned char>(buffer[j])) << " ";
            }
            else {
                cout << "   ";
            }
            if (j == 7) cout << " ";
        }

        if (showBinary) {
            cout << " | ";
            for (size_t j = 0; j < bytesRead; ++j) {
                cout << byteToBinary(buffer[j]) << " ";
            }
        }

        cout << " |";
        for (size_t j = 0; j < bytesRead; ++j) {
            cout << (isprint(buffer[j]) ? buffer[j] : '.');
        }
        cout << "|" << endl;
    }

    cout << "\nPage: " << page + 1
        << "  Total: " << (fileSize + pageSize - 1) / pageSize
        << "  Size: " << fileSize << " bytes"
        << "  Mode: " << (showBinary ? "HEX+BIN+ASCII" : "HEX+ASCII") << endl;
}
int main() {
    setlocale(LC_ALL, "RUS");
    string filename;
    int page = 0;
    bool showBinary = false;

    cout << "путь к файлу: ";
    getline(cin, filename);

    while (true) {
        system("cls");
        printHexDump(filename, page, 256, showBinary);

        cout << "\nControls: [N]ext [P]rev [B]inary [E]dit [Q]uit\nCommand: ";
        char cmd;
        cin >> cmd;
        cin.ignore();

        switch (toupper(cmd)) {
        case 'N': page++; break;
        case 'P': page = max(page - 1, 0); break;
        case 'B': showBinary = !showBinary; break;
        case 'E': {
            string addrStr, valueStr, mode;
            size_t address;
            unsigned char value;

            cout << "ввеидте адрес (hex): ";
            getline(cin, addrStr);
            try {
                address = stoul(addrStr, nullptr, 16);
            }
            catch (...) {
                cout << "неккоректный адрес";
                break;
            }

            cout << "Edit mode [H]ex/[B]inary: ";
            getline(cin, mode);
            std::transform(mode.begin(), mode.end(), mode.begin(), ::toupper);

            cout << "введите значение: ";
            getline(cin, valueStr);
            try {
                if (mode == "H") {
                    if (valueStr.size() != 2) throw invalid_argument("");
                    value = stoul(valueStr, nullptr, 16);
                }
                else if (mode == "B") {
                    if (valueStr.size() != 8 ||
                        valueStr.find_first_not_of("01") != string::npos) {
                        throw invalid_argument("");
                    }
                    value = bitset<8>(valueStr).to_ulong();
                }
                else {
                    throw invalid_argument("");
                }
            }
            catch (...) {
                cout << "некорректное значение";
                break;
            }

            try {
                editFile(filename, address, value);
                cout << "успешно";
            }
            catch (const exception& e) {
                cout << "НЕ успешно: " << e.what();
            }
            Sleep(1500);
            break;
        }
        case 'Q': return 0;
        }
    }
}
