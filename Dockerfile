FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# install dependencies
RUN apt-get update ; apt-get install -y \
    sudo \
    git \
    build-essential \
    libboost-all-dev \
    cmake  \
    python3-dev \
    python3-pip 

RUN pip3 install pipenv

# copy project's source code
RUN git clone https://github.com/ianczyko/method-development-visualizer-backend.git
WORKDIR /method-development-visualizer-backend

# Compile the C++ part
RUN cd methodDevelopment ; mkdir build ; cd build ; cmake .. ; make

# Install Django
WORKDIR /method-development-visualizer-backend/web
RUN pipenv install django==3.1.3

WORKDIR /method-development-visualizer-backend
EXPOSE 8000