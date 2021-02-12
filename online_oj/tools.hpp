#pragma once 
// 为各个模块提供工具API
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/algorithm/string.hpp>

class StringSplit
{
  public:
    static void Split(const std::string& input, const std::string& split_char, std::vector<std::string>* output)
    {
      boost::split(*output, input, boost::is_any_of(split_char), boost::token_compress_off);
    }
};
class Urlcode 
{
  public:
    static void PraseBody(const std::string& body, std::unordered_map<std::string, std::string>* kv_map)
    {
      // 1.先按照&切分成不同的key:value形式
      std::vector<std::string> kv_vec;
      StringSplit::Split(body, "&", &kv_vec);
      // 2.再按照=把key和value切开
      for (const auto str : kv_vec)
      {
        std::vector<std::string> kv_sig;
        StringSplit::Split(str, "=", &kv_sig);
        if (kv_sig.size() != 2)
          continue;
        // 3.保存到kv_map中返回给上层调用者
        (*kv_map)[kv_sig[0]] = UrlDecode(kv_sig[1]);
      }
    }
    static unsigned char FromHex(unsigned char x)   
    {   
      unsigned char y;  
      if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
      else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
      else if (x >= '0' && x <= '9') y = x - '0';  
      else assert(0);  
      return y;  
    }  
    static std::string UrlDecode(const std::string& str)  
    {  
      std::string strTemp = "";  
      size_t length = str.length();  
      for (size_t i = 0; i < length; i++)  
      {  
        if (str[i] == '+') strTemp += ' ';  
        else if (str[i] == '%')  
        {  
          assert(i + 2 < length);  
          unsigned char high = FromHex((unsigned char)str[++i]);  
          unsigned char low = FromHex((unsigned char)str[++i]);  
          strTemp += high*16 + low;  
        }  
        else strTemp += str[i];  
      }  
      return strTemp;  
    } 
};
class FileUtil
{
  public:
    static bool ReadFile(const std::string& file_path, std::string* output)
    {
      (*output).clear();
      std::ifstream file(file_path.c_str());
      if (!file.is_open())
      {
        perror("open_file");
        return false;
      }
      std::string buffer;
      while (std::getline(file, buffer))
      {
        (*output) += buffer + "\n";
      }
      file.close();
      return true;
    }
    static bool WriteFile(const std::string& file_name, const std::string& data)
    {

      return true;
    }
};
