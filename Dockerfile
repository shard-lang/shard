FROM ubuntu:16.04

ARG PKG
ARG CC
ARG CXX

ENV CC=$CC CXX=$CXX GTEST_COLOR=1 VERBOSE=1

RUN apt-get -y update
RUN apt-get -y install cmake git $PKG

RUN mkdir -p /opt/shard/build
WORKDIR /opt/shard/build
