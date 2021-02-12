#pragma once 
// 核心逻辑：获取并渲染html模板
#include <iostream>
#include <jsoncpp/json/json.h>

#include "oj_model.hpp"
#include "ctemplate/template.h"

class Oj_View
{
  public:
    static void FillAllQuestions(const std::vector<Questions>& all_vec, std::string* html)
    {
      // 1.创建一个模板字典
      ctemplate::TemplateDictionary dic("all_ques");
      // 2.创建子字典
      for (auto& ques : all_vec)
      {
        ctemplate::TemplateDictionary* sub_dic = dic.AddSectionDictionary("question");

        sub_dic->SetValue("id", ques.id_);
        sub_dic->SetValue("title", ques.title_);
        sub_dic->SetValue("star", ques.star_);
      }
      // 3.读取html模板
      ctemplate::Template* tl = ctemplate::Template::GetTemplate("./template_pretty/all_questions.html", ctemplate::DO_NOT_STRIP);
      // 4.设置渲染体
      tl->Expand(html, &dic);
    }
    static void FillOneQuestion(const Questions& question, std::string* html)
    {
      // 1.创建一个字典
      ctemplate::TemplateDictionary dic("one_ques");
      // 2.设置字典内容
      dic.SetValue("id", question.id_);
      dic.SetValue("title", question.title_);
      dic.SetValue("star", question.star_);

      dic.SetValue("desc", question.desc_);
      dic.SetValue("code", question.head_);
      // 3.读取html模板
      ctemplate::Template* tl = ctemplate::Template::GetTemplate("./template_pretty/question.html", ctemplate::DO_NOT_STRIP);
      // 4.设置渲染体
      tl->Expand(html, &dic);
    }
    static void FillResponse(const Json::Value& Resp, std::string* html)
    {
      // 1.创建一个字典
      ctemplate::TemplateDictionary dic("resp");
      // 2.设置字典内容
      dic.SetValue("errno", Resp["errno"].asString());
      dic.SetValue("reason", Resp["reason"].asString());
      dic.SetValue("stdout", Resp["stdout"].asString());
      // 3.获取html模板
      ctemplate::Template* tl = ctemplate::Template::GetTemplate("./template_pretty/response.html", ctemplate::DO_NOT_STRIP);
      // 4.设置渲染体
      tl->Expand(html, &dic);
    }
};
