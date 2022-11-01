# Minpass backend

A minimal password manager written in C++ as a REST API which can be used with any client.
This project aims to create a server sitting on your machine or hosted on a device like raspberry pi.
You should be able to send and receive requests from this device across your local network once a port is open.

I recommend using the docker image if you can.

**Note:** Don't use your real passwords for testing. There is no encryption and user authencation.
This is a v0.0.1 alpha release.

## Why C++ ?

It is harder to this C++ but the fast run time of C++ and the async nature drogon framework motivated me.

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

Pull image from docker hub.

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

<!-- Todo: Add video demos -->
<!-- Show postman -->
<!-- Show corresponding curl and powershell commands -->

## Frameworks and tools used

- [drogon](https://github.com/drogonframework/drogon)
- [fmt](https://github.com/fmtlib/fmt)
- I would like to mention [Thunder Client](https://www.thunderclient.com/) tool, I have used for the demo.

## Goals

- Encryption.
- CMake install.
- User authentication.
- Reduce executable size.
- Securing API.
- Better Documentation for functions
- An example client in both C++ and ReactJS for desktop and browser access.
- Add a way to automatically open ports while installation.
