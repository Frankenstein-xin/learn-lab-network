FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y cmake g++ gdb build-essential git vim net-tools iproute2 iputils-ping
RUN mkdir -p /dev/net && mknod /dev/net/tun c 10 200 && chmod 600 /dev/net/tun
RUN mkdir ~/source && cd ~/source && git clone https://github.com/Frankenstein-xin/learn-lab-network.git
