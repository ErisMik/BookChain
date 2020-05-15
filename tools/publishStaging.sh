#!/bin/bash

# Bookchain Staging Publish Script
# Run from root directory

BC_STAGING_DOCKER_TAG="staging"
echo "Pushing to dockerhub with tag \"${BC_STAGING_DOCKER_TAG}\""

echo "Building client image"
docker build bookchain-client -t itseris/bookchain-client:${BC_STAGING_DOCKER_TAG}

echo "Building miner image"
docker build bookchain-miner -t itseris/bookchain-miner:${BC_STAGING_DOCKER_TAG}

echo "Pushing client image to dockerhub"
docker push itseris/bookchain-client:${BC_STAGING_DOCKER_TAG}

echo "Pushing miner image to dockerhub"
docker push itseris/bookchain-miner:${BC_STAGING_DOCKER_TAG}
