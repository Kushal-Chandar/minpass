FROM drogonframework/drogon:latest

WORKDIR /minpass

COPY . .

RUN apt update -y \
  && apt install -y \
  git \
  ccache \
  curl \
  zip \
  jq \
  unzip \
  tar \
  python3 \
  ninja-build \
  clang \
  pkg-config \
  doxygen \
  libfmt-dev \
  && apt upgrade -y

RUN ./scripts/get_cmake_ubuntu_docker.sh

WORKDIR /minpass/build
RUN cmake -S .. -B . -G Ninja && ninja

ENV PORT=8080

EXPOSE 8080

RUN ./tests/minpass_tests.cc -s

CMD [ "minpass.exe" ]
