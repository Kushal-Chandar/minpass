#define DROGON_TEST_MAIN
#include <drogon/drogon.h>
#include <drogon/drogon_test.h>

auto main(int argc, char *argv[]) -> int {
  std::promise<void> promise;
  std::future<void> future = promise.get_future();

  drogon::app().loadConfigFile("./server_config_test.json");
  // Start the main loop on another thread
  std::thread thr([&promise]() {
    // Queues the promise to be fulfilled after starting the loop
    drogon::app().getLoop()->queueInLoop([&promise]() { promise.set_value(); });
    drogon::app().run();
  });

  // The future is only satisfied after the event loop started
  future.get();
  int status = drogon::test::run(argc, argv);

  // Ask the event loop to shutdown and wait
  drogon::app().getLoop()->queueInLoop([]() { drogon::app().quit(); });
  thr.join();
  return status;
}
