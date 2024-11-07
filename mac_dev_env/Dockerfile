FROM ubuntu:20.04
RUN apt update && apt install -y cmake g++ gdb build-essential git vim net-tools iproute
RUN mkdir -p /dev/net && mknod /dev/net/tun c 10 200 && chmod 600 /dev/net/tun