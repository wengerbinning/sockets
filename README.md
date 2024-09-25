# sockets
This is a packet sending tool that can send any data you want.















sys/socket.h
-------------

int socket (int __domain, int __type, int __protocol);
int socketpair (int __domain, int __type, int __protocol, int __fds[2]);
int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
int listen (int __fd, int __n);
int accept (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);

ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);
ssize_t sendto (int __fd, const void *__buf, size_t __n, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len);
ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);
ssize_t sendmsg (int __fd, const struct msghdr *__message, int __flags);
ssize_t recvmsg (int __fd, struct msghdr *__message, int __flags);
int sendmmsg (int __fd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags);
int recvmmsg (int __fd, struct mmsghdr *__vmessages, unsigned int __vlen, int __flags,struct timespec *__tmo);

int getsockname (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __len);
int getpeername (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __len);
int getsockopt (int __fd, int __level, int __optname, void *__restrict __optval,socklen_t *__restrict __optlen);
int setsockopt (int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen);
int accept4 (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len, int __flags);
int shutdown (int __fd, int __how);
int sockatmark (int __fd);
int isfdtype (int __fd, int __fdtype);