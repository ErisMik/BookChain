# Bookchain - Miner Dockerfile


## Prebuild image
FROM debian:buster-slim AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y git build-essential cmake clang-tidy
RUN apt-get update -y && apt-get install -y libboost-dev libboost-test-dev libssl-dev libzmq5-dev
RUN bash -c "git clone git://github.com/zeromq/zmqpp.git && \
             cd zmqpp && \
             make -j8 && \
             make check && \
             make install && \
             make installcheck"

RUN mkdir -p /bookchain/build/build

COPY src/ ./

WORKDIR /bookchain/build/build
RUN cmake ../ && make -j8


## Runtime image
FROM debian:buster-slim AS run
RUN mkdir -p /bookchain/miner
WORKDIR /bookchain/miner

RUN apt-get update -y && apt-get install -y gdb
RUN apt-get update -y && apt-get install -y libboost-dev libssl-dev libzmq5

COPY --from=build /bookchain/build/build/miner ./

CMD ["./miner"]
