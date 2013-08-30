/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

/* socket起源于Unix，而Unix/Linux基本哲学之一就是“一切皆文件”，都可以用“打开open –> 读写write/read –> 关闭close”模式来操作 */

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

    /*  Create a socket for the client.  */

    /** API
     * int socket(int family, int type, int protocol); 
     *
     * family
     *  AF_INET	        IPv4协议
     *  AF_INET6	IPv6协议
     *  AF_LOCAL(AF_UNIX)	Unix域协议（Unix domain protocols）
     *
     * type
     *  SOCK_STREAM	TCP
     *  SOCK_DGRAM	UDP
     *  SOCK_RAW	RAW Socket
     */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */
/*  对TCP而言，connect()引发三次握手。UDP通常直接通过sendto()发送报文而无需connect()。 */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}
