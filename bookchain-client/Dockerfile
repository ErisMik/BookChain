# Bookchain - Client Dockerfile


## Prebuild image
FROM node:13 AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

COPY package.json yarn.lock jsconfig.json ./
RUN yarn install

COPY public/ public/
COPY src/ src/
RUN yarn build


## Runtime image
FROM nginx:latest AS run

COPY --from=build /bookchain/build/build /usr/share/nginx/html
