# Bookchain - Miner Dockerfile


## Prebuild image
FROM debian:buster-slim AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y build-essential cmake clang-tidy libboost-dev libssl-dev

RUN mkdir -p /bookchain/build/build

COPY src/ ./

WORKDIR /bookchain/build/build
RUN cmake ../ && make -j8


## Runtime image
FROM debian:buster-slim AS run
RUN mkdir -p /bookchain/miner
WORKDIR /bookchain/miner

RUN apt-get update -y && apt-get install -y libboost-dev libssl-dev gdb

COPY --from=build /bookchain/build/build/miner ./

CMD ["./miner"]
