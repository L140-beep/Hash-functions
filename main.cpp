#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <chrono>

std::string XOR(std::string left, std::string right){

    if (left.length() != right.length()){
        throw "Other length!";
    }
    std::string result = "";
    int check_zeros = 0;
    for (auto l_iter = left.begin(), r_iter(right.begin()); l_iter != left.end(); l_iter++, r_iter++){
        if (*l_iter == *r_iter){
            if(check_zeros == 0 ){
                continue;
            }
            result = result + "0";
        }
        else {
            check_zeros = 1;
            result = result + "1";
        }
    }

    return result;
}

int convert(std::string data, int base)
{
    int result = 0;
    int digit = data.length() - 1;
    for (std::string::iterator iter = data.begin(); iter != data.end(); iter++, digit--){
        result += (*iter - '0') * std::pow(base, digit);
    }

    return result;
}

std::string to_bin(int data){

    std::string str = "";
    if(data == 0){
        return "0";
    }
    while(data > 0){
        str = std::to_string(data % 2) + str;
        data /= 2;
    }

    return str;
}

std::string to_bin(std::string data)
{
    std::string bin_str;
    int int_data = 0;
    for (std::string ::iterator iter = data.begin(); iter != data.end(); iter++)
    {
        int_data = static_cast<int>(*iter);
        bin_str = to_bin(int_data) + bin_str;
    }

    return bin_str;
}

std::string get_data(std::string path){

    std::ifstream f(path);
    std::string str = "";
    std::string temp_str = "";
    while (f)
    {
        getline(f, temp_str);
        str += temp_str;
    }

    f.close();
    return str;

}

int CRC24(std::string data)
{
    data = to_bin(data);
    const int POLINOM = 0x15D6DCB; // Интересно, что CRC-16 дает ответ 66
    std::string str_polinom = to_bin(POLINOM);
    int POLINOM_SIZE = str_polinom.length();
    data += std::string(POLINOM_SIZE - 1, '0');

    while (data.length() >= POLINOM_SIZE){
        data = XOR(data.substr(0, POLINOM_SIZE), str_polinom) + data.substr(POLINOM_SIZE);
    }

    return convert(data, 2);
}

int PJW(std::string data){

    int hash = 0;
    int temp = 0;
    for (std::string::iterator iter = data.begin(); iter != data.end(); iter++){
        hash = (hash << 4) + static_cast<int>(*iter);
        temp = hash & 0xf0000000;
        if (temp != 0)
        {
            hash = hash ^ (temp >> 24);
            hash = hash & 0xfffffff;
        }
    }

    return hash;
}

class R_class{
public:
    static int R(char ch)
        {
            static std::map<char, int> mp;
            std::map<char, int>::iterator iter = mp.find(ch);
            if (iter == mp.end())
            {
                int result = CRC24(std::to_string(ch));
                mp.insert(std::pair<char, int>(ch, result));
                return result;
            }

            return iter->second;
    }
};

int BUZ(std::string data){
    int hash = 0;
    int highorder = 0;
    for (std::string::iterator iter = data.begin(); iter != data.end(); iter++){
        highorder = hash & 0x80000000;
        hash = hash << 1;
        hash = hash ^ (highorder >> 31);
        hash = hash ^ R_class::R(*iter);
    }

    return hash;
}

int dublicate_search(std::string path, std::function<int(std::string)> hash)
{
    int dublicates = 0;
    int *arr = new int[500];
    for (int i = 0; i < 500; i++){
        std::string data = get_data(path + std::to_string(i) + ".txt");

        arr[i] = hash(data);
    }

    for (int i = 0; i < 500; i++){
        for (int j = i + 1; j < 500; j++){
            if (arr[i] == arr[j]){
                dublicates++;
            }
        }
    }

    return dublicates;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    int result = dublicate_search("./out/", CRC24);
    auto end = std::chrono::steady_clock::now();
    std::cout << "CRC24: " << result << std::endl;
    std::cout << "time: " << std::chrono::duration<double, std::milli>(end - start).count() / 1000 << "s" << std::endl;
    start = std::chrono::steady_clock::now();
    result = dublicate_search("./out/", PJW);
    end = std::chrono::steady_clock::now();
    std::cout << "PJW: " << result << std::endl;
    std::cout << "time: " << std::chrono::duration<double, std::milli>(end - start).count() / 1000 << "s" << std::endl;
    start = std::chrono::steady_clock::now();
    result = dublicate_search("./out/", BUZ);
    end = std::chrono::steady_clock::now();
    std::cout << "BUZ: " << result << std::endl;
    std::cout << "time: " << std::chrono::duration<double, std::milli>(end - start).count() / 1000 << "s" << std::endl;
}