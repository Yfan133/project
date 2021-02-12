#pragma once
// 核心逻辑：读文件，对内容进行切分
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "tools.hpp"

// 试题的属性
struct Questions 
{
  std::string id_;
  std::string title_;
  std::string star_;
  std::string path_;

  std::string desc_;
  std::string head_;
  std::string tail_;
};
// 对试题进行操作
class Oj_Model
{
  public:
    Oj_Model()
    {
      Load("./oj_data/oj_config.cfg");
    }
    ~Oj_Model()
    {}
    bool Load(const std::string& file_path)
    {
      // 1.操作文件
      std::ifstream file(file_path.c_str());
      if (!file.is_open())
      {
        // 内部错误，打印日志信息
        perror("open_file");
        return false;
      }
      // 2.对文件内容进行切分，并保存
      std::string buffer;
      while (std::getline(file, buffer))
      {
        std::vector<std::string> vec;
        StringSplit::Split(buffer, " ", &vec);
        Questions ques;
        ques.id_ = vec[0];
        ques.title_ = vec[1];
        ques.star_ = vec[2];
        ques.path_ = vec[3];

        std::string dir = vec[3];
        FileUtil::ReadFile(dir + "/desc.txt", &ques.desc_);
        FileUtil::ReadFile(dir + "/header.cpp", &ques.head_);
        FileUtil::ReadFile(dir + "/tail.cpp", &ques.tail_);

        ques_map[ques.id_] = ques;
      }
      // 3.关闭文件描述符
      file.close();
      return true;
    }
    bool GetAllQuestions(std::vector<Questions>* ques_vec)
    {
      for (const auto it : ques_map)
      {
        (*ques_vec).push_back(it.second);
      }
      sort((*ques_vec).begin(), (*ques_vec).end(), [](Questions& q1, Questions& q2){
          return std::stoi(q1.id_) < std::stoi(q2.id_);
          });
      return true;
    }
    bool GetOneQuestion(const std::string& id, Questions* questions)
    {
      auto it = ques_map.find(id);
      if (it == ques_map.end())
      {
        printf("No Such Id\n");
        return false;
      }
      *questions = it->second;
      return true;
    }
  private:
    std::unordered_map<std::string, Questions> ques_map;
};
