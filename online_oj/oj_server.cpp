#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "httplib.h"
#include "oj_model.hpp"
#include "oj_view.hpp"
#include <json/json.h>

using namespace httplib;
int main()
{
  Server svr;
  Oj_Model model;
  // 1.注册获取所有试题方法
  svr.Get("/all_questions", [&model](const Request& req, Response& resp){
      // 1.从试题模块中获取试题列表
      std::vector<Questions> ques_vec;
      model.GetAllQuestions(&ques_vec);
      // 2.设置响应体
      std::string html;
      Oj_View::FillAllQuestions(ques_vec, &html);
      resp.set_content(html, "text/html");
      });
  // 2.注册获取单个试题方法
  svr.Get(R"(/question/(\d+))", [&model](const Request& req, Response& resp){
      // 1.根据正则表达式的题号，获取具体信息
      Questions question;
      model.GetOneQuestion(req.matches[1], &question);
      // 2.根据不同题号设置响应体
      std::string html;
      Oj_View::FillOneQuestion(question, &html);
      resp.set_content(html, "text/html");
      });
  // 3.注册编译运行方法
  svr.Post(R"(/compile/(\d+))", [&model](const Request& req, Response& resp){
      // 1.获取单个试题的详细信息
      Questions question;
      model.GetOneQuestion(req.matches[1], &question);
      for (auto it : req.matches)
        std::cout << it << std::endl;
      // 2.切分请求url，分成不同key:value形式，然后进行url解码
      std::unordered_map<std::string, std::string> kv_map;
      Urlcode::PraseBody(req.body, &kv_map);
      // 3.将提交的code和tail结合，创建一个临时文件
      std::string code = kv_map["code"];
      std::string std_in = kv_map["stdin"];
      Json::Value Req_Js;
      Json::Value Resp_Js;
      Req_Js["code"] = code + question.tail_;
      Req_Js["stdin"] = std_in;
      // 4.编译运行
      
      // 5.设置响应体
      
      });
  svr.set_base_dir("./wwwroot");
  svr.listen("0.0.0.0", 18888);
  return 0;
}
