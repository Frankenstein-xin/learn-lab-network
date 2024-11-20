## Tun
- A un device will up only when the tun device is "connected" to an application 
- Reference this article for more information https://www.cnblogs.com/charlieroro/p/13497340.html

## How to have fun
### Create a tun device
```bash
openvpn --mktun --dev tun93
ip link set tun93 up
ip addr add 10.0.0.1/24 dev tun93
```

### Associate this tun device to this application
```bash
# Open another console and execute the following commands
make
./tun_tap tun93
```

### Have fun
```bash
ping 10.0.0.2

# then you will see outputs in the console above
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
Read 84 bytes from tun/tap device
```