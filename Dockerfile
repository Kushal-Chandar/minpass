FROM drogonframework/drogon:latest

RUN apt-get update -y \
  && apt-get install -y \
  ccache \
  curl \
  tar \
  jq \
  ninja-build \
  libsqlite3-dev \
  clang \
  libfmt-dev \
  && apt-get purge --auto-remove cmake \
  && apt-get upgrade -y

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

WORKDIR /app

RUN cp /build/minpass /build/server_config.json .\
  && rm -rf /build

RUN apt-get remove -y \
  jq \
  ninja-build \
  libsqlite3-dev \
  clang \
  libfmt-dev \
  && apt-get auto-remove -y

CMD [ "./minpass" ]
