# Project Trade

Project Trade is a C++ application designed to interact with the Binance API for trading purposes.
## I. Compilation Instructions

To compile the project from source, follow these steps:

### 1. Build the Project on your Local Machine

```
mkdir build && cd build
cmake ..
make
```

### 2. Run the Application

```
./src/trade
```

### II. Build and Run the Project Using Docker

Building the Docker Image
Navigate to the project directory and run:

```
docker build -t trade .
```


Running the Docker Container
To run your project in a Docker container, execute:

```
docker run --name tradecontainer trade
```
