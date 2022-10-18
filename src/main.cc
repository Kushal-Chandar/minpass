#include <drogon/drogon.h>
#include <fmt/core.h>

#include <chrono>
#include <fstream>

auto main() -> int {
  // Json::Value root;
  // std::ifstream server_config("./server_config.json");
  // server_config >> root;

  // const auto listeners = root["listeners"];

  // for (auto& listener : listeners) {
  //   fmt::print("{}\n{}\n{}\n{}\n{}\n", listener["address"].asString(),
  //              listener["port"].asString(), listener["ssl_cert"].asString(),
  //              listener["ssl_key"].asString(),
  //              listener["use_https"].asBool());
  // }
  // fmt::print("{}\n", root["sqlite3_database_name"].asString());
  // drogon::orm::DbClientPtr newMysqlClient(const std::string& connInfo,
  //                                         const size_t connNum);
  // drogon::app().createDbClient();  // drogon::app()
  //     .setLogPath("./")
  //     .setLogLevel(trantor::Logger::kWarn)
  //     .addListener("0.0.0.0", 80)
  //     .setThreadNum(0);

  drogon::app()
      .createDbClient("sqlite3", "127.0.0.1", 8008, "minpass", "user", "passwd",
                      1)
      .run();

  // auto custom_config = drogon::app().getCustomConfig();
  // fmt::print("{}\n", custom_config.asString());

  // drogon.run();
  return EXIT_SUCCESS;
}
