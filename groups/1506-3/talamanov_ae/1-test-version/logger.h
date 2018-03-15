#ifndef TALAMANOV_AE_TEST_VERSION_CHECKER_LOGGER_H
#define TALAMANOV_AE_TEST_VERSION_CHECKER_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

enum class verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class Logger {
public:
  enum class ext_cls{
    NO      = 1,
    VERDICT = 2,
    MESSAGE = 3,
    TIME    = 4,
    MEMORY  = 5
  };

  Logger(const std::string& log_file_path) {
    log_file_.open(log_file_path, std::ios::app);
  }

  ~Logger() {
    log_file_ << std::endl;
    log_file_.close();
  }

  void writeType(ext_cls type) { log_file_ << static_cast<int>(type) << std::endl; }

  void writeVerdict(verdict v) {
    writeType(ext_cls::VERDICT);
    log_file_ << static_cast<int>(v) << std::endl;
  }

  void writeMessage(const std::string& msg) {
    writeType(ext_cls::MESSAGE);
    log_file_ << msg << std::endl;
  }

  void writeTime(long long time_ns) {
    writeType(ext_cls::TIME);
    log_file_ << time_ns << std::endl;
  }

  void writeMemory(long long memory_b) {
    writeType(ext_cls::MEMORY);
    log_file_ << memory_b << std::endl;
  }

private:
  std::ofstream log_file_;
};

#endif //TALAMANOV_AE_TEST_VERSION_CHECKER_LOGGER_H
