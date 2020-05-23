#!/bin/bash

# Bookchain Multiarch Publish Script
# Run from root directory

BC_MULTIARCH_DOCKER_TAG="multiarch"

# Need to have experimental CLI and Engine (buildx + buildkit)
export DOCKER_CLI_EXPERIMENTAL=enabled
export DOCKER_BUILDKIT=enabled

# Add QEMU stuff
docker run --rm --privileged multiarch/qemu-user-static --reset -p yes

# Create and bootstrap builder
docker buildx create --name mubuilder
docker buildx use mubuilder
docker buildx inspect --bootstrap

# Build and push images
docker buildx build bookchain-client -t itseris/bookchain-client:${BC_MULTIARCH_DOCKER_TAG} --push --platform "linux/amd64,linux/arm64,linux/arm/v7"
docker buildx build bookchain-miner -t itseris/bookchain-miner:${BC_MULTIARCH_DOCKER_TAG} --push --platform "linux/amd64,linux/arm64,linux/arm/v7"

# Cleanup
# docker buildx rm mubuilder
