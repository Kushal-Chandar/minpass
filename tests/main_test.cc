#define DROGON_TEST_MAIN
#include <drogon/drogon.h>
#include <drogon/drogon_test.h>

auto main(int argc, char *argv[]) -> int {
  std::promise<void> p1;
  std::future<void> f1 = p1.get_future();

  drogon::app().loadConfigFile("./server_config_test.json");
  // Start the main loop on another thread
  std::thread thr([&]() {
    // Queues the promise to be fulfilled after starting the loop
    drogon::app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
    drogon::app().run();
  });

  // The future is only satisfied after the event loop started
  f1.get();
  int status = drogon::test::run(argc, argv);

  // Ask the event loop to shutdown and wait
  drogon::app().getLoop()->queueInLoop([]() { drogon::app().quit(); });
  thr.join();
  return status;
}
