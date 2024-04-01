# Start from an Ubuntu 20.04 image
FROM ubuntu:20.04

# Set the working directory inside the container
WORKDIR /usr/src/app

# Prevent apt-get from interacting with user
ARG DEBIAN_FRONTEND=noninteractive

# Install build essentials and OpenSSL development libraries
RUN apt-get update && \
    apt-get install -y build-essential libssl-dev cmake git && \
    rm -rf /var/lib/apt/lists/*

# Copy the project files into the container
COPY . .

RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make
