#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/if_tun.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

using namespace std;

/**
 * Create tun interface, note that the /dev/net/tun is a clone device,
 * the actuall device name will be created after the ioctl successfully allocated
 * and the ifr.ifr_name indicates the name of the new tun device, normally the name is (tun + acc number)
 */
int tun_alloc(char *dev, int flags) {
 
    struct ifreq ifr;
    int fd, err;
    char *clonedev = "/dev/net/tun";
    
    /* Arguments taken by the function:
    *
    * char *dev: the name of an interface (or '\0'). MUST have enough
    *   space to hold the interface name if '\0' is passed
    * int flags: interface flags (eg, IFF_TUN etc.)
    */
    
    /* open the clone device */
    if( (fd = open(clonedev, O_RDWR)) < 0 ) { /* 使用读写方式打开 */
        return fd;
    }
    
    /* preparation of the struct ifr, of type "struct ifreq" */
    memset(&ifr, 0, sizeof(ifr));
    
    ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */
    
    if (*dev) {
        /* if a device name was specified, put it in the structure; otherwise,
        * the kernel will try to allocate the "next" device of the
        * specified type */
        strncpy(ifr.ifr_name, dev, IFNAMSIZ); /* 设置设备名称 */
    }
    
    /* try to create the device */
    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
        close(fd);
        return err;
    }
    
    /* if the operation was successful, write back the name of the
    * interface to the variable "dev", so the caller can know
    * it. Note that the caller MUST reserve space in *dev (see calling
    * code below) */
    strcpy(dev, ifr.ifr_name);
    
    /* this is the special file descriptor that the caller will use to talk
    * with the virtual interface */
    return fd;
}

/**
 * https://github.com/mozhuli/SDN-Learning-notes/blob/master/linux/tun-tap.md
 * https://www.cnblogs.com/charlieroro/p/13497340.html
 */
int main(int argc, char *argv[])
{
    int tun_fd, nread;
    char buffer[1500];

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *        IFF_NO_PI - Do not provide packet information
     */
    char tun_name[IFNAMSIZ];
    strcpy(tun_name, argv[1]);
    tun_fd = tun_alloc(tun_name, IFF_TUN | IFF_NO_PI);

    if (tun_fd < 0) {
        perror("Allocating interface");
        exit(1);
    }

    while (1) {
        nread = read(tun_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Reading from interface");
            close(tun_fd);
            exit(1);
        }

        printf("Read %d bytes from tun/tap device\n", nread);
    }
    return 0;
}