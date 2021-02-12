#pragma once 
// 编译运行代码，并处理结果
#include <jsoncpp/json/json.h>

#include <iostream>
#include <string>

enum ErrorNo
{
  OK = 0,
  PRAM_ERROR,       // 参数错误
  INTERNAL_ERROR,   // 内部错误
  COMPILE_ERROR,    // 编译错误
  RUN_ERROR         // 运行错误
};
class Compiled
{
  public:
    static void CompileAndRun(const Json::Value& Req, Json::Value* Resp)
    {
      // 1.检查参数正确性
      // 2.将内存中code写道文件中去
      // 3.编译模块
      // 4.运行模块
      // 5.设置响应
      // 6.清理临时文件
    }
  private:
    void Clean()
    {

    }
    bool Compile()
    {

    }
    bool Run()
    {

    }
  private:
    std::string StdoutPath(const std::string& filename)
    {
      // 运行结果
      return "./tmp_file/" + filename + ".stdout";
    }
    std::string StderrorPath(const std::string& filename)
    {
      // 运行错误
      return "./tmp_file/" + filename + ".stderror";
    }
    std::string ErrorPath(const std::string& filename)
    {
      // 编译错误
      return "./tmp_file/" + filename + ".compile_error";
    }
    std::string ExePath(const std::string& filename)
    {
      // 可执行文件
      return "./tmp_file/" + filename + ".exe";
    }
    std::string SrcPath(const std::string& filename)
    {
      // 源文件
      return "./tmp_file/" + filename + ".cpp";
    }
};
