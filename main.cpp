#include <iostream>
#include <functional>
#include <fstream>
#include <string>

std::string int_to_bin(int data){

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

std::string string_to_bin(std::string data)
{
    std::string bin_str;
    int int_data = 0;
    for (std::string ::iterator iter = data.begin(); iter != data.end(); iter++)
    {
        int_data = static_cast<int>(*iter);
        bin_str = int_to_bin(int_data) + bin_str;
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

int CRC16(std::ifstream file)
{
    const int polinom = 0x18005;
    // const int polinom = 0x19;
    
    return 0;
}

int dublicate_search(std::string path, std::function<void()> foo)
{
    int dublicates = 0;

    for (int i = 0; i < 1; i++){
        std::string data = get_data(path + std::to_string(i) + ".txt");
        data = string_to_bin(data);
        std::cout << data << std::endl;
    }

        return dublicates;
}

void moo()
{
    std::cout << "moo" << std::endl;
}

int main()
{
    dublicate_search("./out/", moo);
}