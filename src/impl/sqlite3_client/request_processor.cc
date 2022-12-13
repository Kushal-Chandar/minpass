#include "sqlite3_client/request_processor.h"

#include <drogon/HttpRequest.h>

#include <optional>

#include "crypto.h"
#include "crypto/aes_gcm_256.h"
#include "sqlite3_client/helpers.h"

namespace minpass::sqlite3_client {

auto RequestProcessor::ParseRequestJson(
    const drogon::HttpRequestPtr &http_request,
    drogon::HttpResponsePtr &http_response, Json::Value &response_object_out)
    -> std::optional<std::tuple<Email, Username, Password, MasterPassword>> {
  auto json = http_request->getJsonObject();
  if (!json || ((*json)["master_password"].asString().empty())) {
    response_object_out["message"] = "could not parse request";
    http_response =
        Helpers::MakeResponse(response_object_out, drogon::k400BadRequest);
    return std::nullopt;
  }
  response_object_out["message"] = "ok";
  http_response =
      Helpers::MakeResponse(response_object_out, drogon::k202Accepted);

  return std::make_tuple(
      Email(((*json)["email"].asString())),
      Username(((*json)["username"].asString())),
      Password(((*json)["password"].asString())),
      MasterPassword(((*json)["master_password"].asString())));
}

auto RequestProcessor::EncryptData(Email &email, Username &username,
                                   Password &password,
                                   MasterPassword &master_password) -> void {
  auto crypto = MinpassCryptoFactory::CreateMinpassCrypto<crypto::AES_GCM_256>(
      master_password.get());
  email = Email(crypto->Encrypt(email.get()));
  username = Username(crypto->Encrypt(username.get()));
  password = Password(crypto->Encrypt(password.get()));
}

auto RequestProcessor::DecryptData(Email &email, Username &username,
                                   Password &password,
                                   MasterPassword &master_password) -> void {
  auto crypto = MinpassCryptoFactory::CreateMinpassCrypto<crypto::AES_GCM_256>(
      master_password.get());
  email = Email(crypto->Decrypt(email.get()));
  username = Username(crypto->Decrypt(username.get()));
  password = Password(crypto->Decrypt(password.get()));
}
}  // namespace minpass::sqlite3_client
