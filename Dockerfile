FROM ubuntu:19.04

ARG PKG
ARG CC
ARG CXX

ENV CC=$CC CXX=$CXX GTEST_COLOR=1 VERBOSE=1

RUN apt-get -y update && apt-get -y install cmake git $PKG

RUN mkdir -p /opt/shard && mkdir -p /opt/build
WORKDIR /opt/build
