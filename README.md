# Minpass backend

A minimal password manager written in C++ as a REST API which can be used with any client.
This project aims to create a server sitting on your machine or hosted on a device like raspberry pi.
You should be able to send and receive requests from this device across your local network once a port is open.

I recommend using the docker image if you can.

**Note:** Don't use your real passwords for testing. There is no user authencation.
This is a v0.0.1 alpha release.

## Why C++ ?

It is harder to this C++ but the fast runtime of C++ and the async nature drogon framework motivated me.

Is C++ is a viable option for building fast and light weight webservers?
I was driven by this question and the answer turns out to be **YES**.

## Building

I recommend the docker way but you can build it your self directly.

```bash
# Clone this repository and cd into it
mkdir build
cd build
cmake -S .. -B .
make # or ninja
```

Please copy the configuration from project directory to build directory before running the app.

## Docker

Install docker desktop and have it running. Now we have 2 options.

### Using the prebuilt docker image

<https://user-images.githubusercontent.com/83660514/199285430-63fb6902-8dd6-4510-aeaf-ede86080d07b.mp4>

Pull image from [dockerhub](https://hub.docker.com/repository/docker/kushalchandar/minpass).

```bash
docker pull kushalchandar/minpass:latest
```

Create a shared volume to persist your passwords.

```bash
docker volume create minpass-sqlite3
```

Run it with.

```bash
docker run -dp 8080:8080 -v minpass-sqlite3:/app kushalchandar/minpass:latest
```

### Building your own docker image and volume

The image will build and automatically start running with this command.

```bash
# Clone this repository and cd into it
docker compose up
```

You can stop the server the way it was shown in usage. Doing this will persist your data.

If you want to stop the server and destroy the data.

```bash
# In project root directory
docker compose down
```

**Note:** If you build an image with docker compose up it will remain in your local images.

## Usage

4 HTTP methods performing 4 operations.

<http://localhost:8080/minpass/SQLite3Client/> is where the app runs.
<http://localhost:8080/minpass/SQLite3Client/website={}> is what we use to send and receive database requests.

I have provided a video with Thunder Client and powershell code to interact with the app the command.

Post:

<https://user-images.githubusercontent.com/83660514/199287006-b5202f23-2643-4b33-a692-96a3e8921a21.mp4>

curl:

```curl

curl -X POST \
  'http://localhost:8080/minpass/SQLite3Client/website=google.com' \
  --header 'Accept: */*' \
  --header 'Content-Type: application/json' \
  --data-raw '{
  "email": "mail@mail.com",
  "username": "pass''22",
  "password": "sk%@8;''sfas0203sd\\d"
}'
```

powershell:

```powershell

$headers = @{}
$headers.Add("Accept", "*/*")
$headers.Add("Content-Type", "application/json")
$reqUrl = 'http://localhost:8080/minpass/SQLite3Client/website=google.com'
$body = '{
  "email": "mail@mail.com",
  "username": "pass''22",
  "password": "sk%@8;''sfas0203sd\\d"
}'
Invoke-RestMethod -Uri $reqUrl -Method Post -Headers $headers -ContentType 'application/json' -Body $body | ConvertTo-Json
```

Patch:

<https://user-images.githubusercontent.com/83660514/199287086-06c18685-994c-44d3-a391-de3fb6e74c27.mp4>

curl:

```curl

curl -X PATCH \
  'http://localhost:8080/minpass/SQLite3Client/website=google.com' \
  --header 'Accept: */*' \
  --header 'Content-Type: application/json' \
  --data-raw '{
  "email": "mail@maiom",
  "username": "pass''",
  "password": "sk%@8\\d"
}'
```

powershell:

```powershell

$headers = @{}
$headers.Add("Accept", "*/*")
$headers.Add("Content-Type", "application/json")
$reqUrl = 'http://localhost:8080/minpass/SQLite3Client/website=google.com'
$body = '{
  "email": "mail@maiom",
  "username": "pass''",
  "password": "sk%@8\\d"
}'
Invoke-RestMethod -Uri $reqUrl -Method Patch -Headers $headers -ContentType 'application/json' -Body $body | ConvertTo-Json
```

Delete:

<https://user-images.githubusercontent.com/83660514/199287317-6814fcd6-a3c4-4584-ac5f-d8ffd193fd0f.mp4>

curl:

```curl

curl -X DELETE \
  'http://localhost:8080/minpass/SQLite3Client/website=google.com' \
  --header 'Accept: */*' \
  --header 'Content-Type: application/json'
```

powershell:

```powershell
$headers = @{}
$headers.Add("Accept", "*/*")
$headers.Add("Content-Type", "application/json")
$reqUrl = 'http://localhost:8080/minpass/SQLite3Client/website=google.com'
Invoke-RestMethod -Uri $reqUrl -Method Delete -Headers $headers -ContentType 'application/json' -Body $body | ConvertTo-Json
```

Get:

curl:

```curl
curl -X GET \
  'http://localhost:8080/minpass/SQLite3Client/website=google.com' \
  --header 'Accept: */*' \
  --header 'Content-Type: application/json'
```

powershell:

```powershell
$headers = @{}
$headers.Add("Accept", "*/*")
$headers.Add("Content-Type", "application/json")
$reqUrl = 'http://localhost:8080/minpass/SQLite3Client/website=google.com'
Invoke-RestMethod -Uri $reqUrl -Method Get -Headers $headers -ContentType 'application/json' -Body $body | ConvertTo-Json
```

## Frameworks and tools used

- [drogon](https://github.com/drogonframework/drogon)
- [fmt](https://github.com/fmtlib/fmt)
- [cryptopp](https://github.com/weidai11/cryptopp)
- I would like to mention [Thunder Client](https://www.thunderclient.com/), I have used it for the demo.

## Goals

- CMake install.
- User authentication.
- Reduce executable size.
- Securing API.
- Better Documentation for functions
- An example client in both C++ and ReactJS for desktop and browser access.
- Add a way to automatically open ports while installation.
