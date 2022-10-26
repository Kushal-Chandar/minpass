FROM kushalchandar/ubuntu-cmake-3.24.2:0.0.1

WORKDIR /minpass

COPY . .

WORKDIR /minpass/build

RUN apt update -y \
    && apt upgrade -y \
    && apt install -y \
    git

RUN apt install -y \
    ccache \
    curl \
    zip \
    unzip \
    tar \
    python3 \
    ninja-build \
    libssl-dev \
    openssl \
    libjsoncpp-dev \
    uuid-dev \
    clang \
    clang++ \
    zlib1g-dev \
    pkg-config  \
    && cmake -S .. -B . -G Ninja \
    && ninja

ENV PORT=8080

EXPOSE 8080

RUN ./tests/minpass_tests.cc -s

CMD [ "minpass.exe" ]
