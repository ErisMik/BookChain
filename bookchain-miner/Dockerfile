# Bookchain - Miner Dockerfile


## Prebuild image
FROM debian:buster-slim AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y build-essential cmake libboost-dev

COPY src/ ./
RUN cmake . && make -j8


## Runtime image
FROM debian:buster-slim AS run
RUN mkdir -p /bookchain/miner
WORKDIR /bookchain/miner

RUN apt-get update -y && apt-get install -y libboost-dev

COPY --from=build /bookchain/build/miner ./

CMD ["./miner"]
