# Minpass backend

A minimal password manager written in C++ as a REST API which can be used with any client. This project aims to create an executable sitting on your computer or hosted on a device like raspberry pi which from where you can request passwords.

The example configuration can be used on your device running on <http://localhost:8080/minpass/SQLite3Client/website={}>

I recommend using the docker image if you can.

**Note:** Don't use your real passwords for testing. There is no encryption and user authencation. This is a v0.0.1 alpha release.

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
