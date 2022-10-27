FROM drogonframework/drogon:latest

RUN apt update -y \
  && apt install -y \
  ccache \
  curl \
  tar \
  jq \
  ninja-build \
  libsqlite3-dev \
  clang \
  libfmt-dev \
  && apt upgrade -y

WORKDIR /minpass

COPY . .

RUN ./scripts/get_cmake_ubuntu_docker.sh

WORKDIR /build

RUN cmake -DCMAKE_BUILD_TYPE:STRING=Release -DDOCKER_BUILD:BOOL=ON -S /minpass -B . -G Ninja \
  && ninja \
  && cp /minpass/server_config.json /build/ \
  && rm -rf /minpass/

ENV PORT=8080

EXPOSE 8080

RUN apt remove -y \
  jq \
  ninja-build \
  libsqlite3-dev \
  clang \
  libfmt-dev \
  && apt auto-remove -y

CMD [ "./minpass" ]
