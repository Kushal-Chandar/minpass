# Minpass backend

A minimal password manager written in C++ as a REST API which can be used with any client. This project aims to create an executable sitting on your computer or hosted on a device like raspberry pi which from where you can request passwords.

The example configuration can be used on your device running on <http://localhost:8080/minpass/SQLite3Client/website={}>

I recommend using the docker image if you can.

**Note:** Don't use your real passwords for testing. There is no encryption and user authencation. This is a v0.0.1 alpha release.

## Building

I recommend the docker way but you can build it your self directly.

```bash
# Clone this repository and cd into it
mkdir build
cd build
cmake -S .. -B .
make # or ninja
```

## Docker

Install docker desktop and have it running. Now we have 2 options.

### Building your own docker image and volume

The image will build and automatically start running with this command.

```bash
# Clone this repository and cd into it
docker compose up
```

You can stop the server the way it was shown in working. Doing this will persist your data.

If you want to stop the server and destroy the data

```bash
# In project root directory
docker compose down
```

**Note:** If you build an image with docker compose up it will remain in your local images.

### Using the prebuilt docker image

## Usage

4 HTTP methods performing 4 operations.

<!-- Todo: Add video demos -->
<!-- Show postman -->
<!-- Show corresponding curl and powershell commands -->

## Goals

- Encryption.
- CMake install.
- User authentication.
- Reduce executable size.
- Securing API.
- Better Documentation for functions
- An example client in both C++ and ReactJS for desktop and browser access.
