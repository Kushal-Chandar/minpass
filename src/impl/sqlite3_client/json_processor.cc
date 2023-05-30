#include "sqlite3_client/json_processor.h"

#include <drogon/HttpRequest.h>

#include <optional>

#include "crypto.h"
#include "crypto/aes_gcm_256.h"
#include "sqlite3_client/helpers.h"

namespace minpass::sqlite3_client {

auto JsonProcessor::ParseRequestJson(const drogon::HttpRequestPtr &http_request,
                                     drogon::HttpResponsePtr &http_response,
                                     Json::Value &response_object_out)
    -> std::optional<PasswordData> {
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

  PasswordData password_data;
  password_data.email.set((*json)["email"].asString());
  password_data.username.set((*json)["username"].asString());
  password_data.password.set((*json)["password"].asString());
  password_data.master_password.set((*json)["master_password"].asString());
  return password_data;
}

auto JsonProcessor::EncryptData(PasswordData &password_data) -> void {
  auto crypto = MinpassCryptoFactory::CreateMinpassCrypto<crypto::AES_GCM_256>(
      password_data.master_password.get());
  password_data.email.set(crypto->Encrypt(password_data.email.get()));
  password_data.username.set(crypto->Encrypt(password_data.username.get()));
  password_data.password.set(crypto->Encrypt(password_data.password.get()));
}

auto JsonProcessor::DecryptData(PasswordData &password_data) -> void {
  auto crypto = MinpassCryptoFactory::CreateMinpassCrypto<crypto::AES_GCM_256>(
      password_data.master_password.get());
  password_data.email.set(crypto->Decrypt(password_data.email.get()));
  password_data.username.set(crypto->Decrypt(password_data.username.get()));
  password_data.password.set(crypto->Decrypt(password_data.password.get()));
}

}  // namespace minpass::sqlite3_client
