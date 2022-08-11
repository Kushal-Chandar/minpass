#include <fmt/core.h>
#include <httplib.h>

#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

auto main() -> int {
  // Get config
  std::ifstream file("./server_config.json");
  json conf = json::parse(file);

  // create server with config
  httplib::SSLServer server(conf.value("ssl_cert", "cert.pem").c_str(),
                            conf.value("ssl_key", "key.pem").c_str());

  server.Get("/hi", [&](const httplib::Request& req, httplib::Response& res) {
    res.set_content(conf.dump(2), "application/json");
  });

  server.Get(R"(/numbers/(\d+))",
             [](const httplib::Request& req, httplib::Response& res) {
               res.set_content(req.matches[1], "text/plain");
             });

  server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content(
        []() {
          std::ifstream file("index.html");
          std::string contents;
          file.seekg(0, std::ios::end);
          contents.resize(file.tellg());
          file.seekg(0, std::ios::beg);
          file.read(&contents[0],
                    static_cast<std::streamsize>(contents.size()));
          file.close();
          contents.pop_back();
          while (contents.back() != '>') {
            contents.pop_back();
          };
          return (
              contents +
              R"(<head><script type="text/javascript" src="https://livejs.com/live.js"></script></head>
              </html>)");
        }(),  // create and invoke lambda immediately
        "text/html");
  });

  // server setup
  server.listen(conf.value("host", "0.0.0.0").c_str(),
                conf.value("port", 8080));

  // fmt::print("{}\n", conf.dump(2));
  return EXIT_SUCCESS;
}
