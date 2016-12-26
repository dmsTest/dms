#include "net_base.h"

void encrypt_msg(char *message,size_t n_size)
{
    while ( *message && n_size-- ) {
        //对message的每一个字符和key进行按位异或
        *message = *message ^ ENCRYPT_KEY;
        message++;
    }
}

void decrypt_msg(char *message,size_t n_size)
{
    while (*message && n_size--) {
        //对message的每一个字符和key进行按位异或
        *message = *message ^ ENCRYPT_KEY;
        message++;
    }
}

unsigned int message_id_crc(const char * sz_message_name_)
{
        unsigned int u_result;
        unsigned char *p_data = (unsigned char *)sz_message_name_;
        if( 0 == p_data[0] ) 
                return (unsigned int)-1;
        u_result = *p_data++ << 24;
        if( *p_data )
        {
                u_result |= *p_data++ << 16;
                if( *p_data )
                {
                        u_result |= *p_data++ << 8;
                        if( *p_data ) u_result |= *p_data++;
                }
        }
        u_result = ~ u_result;
        while( *p_data )
        {
                u_result = (u_result << 8 | *p_data) ^ crc32_table[u_result >> 24];
                p_data++;
        }
        return ~u_result;
}

ssize_t readn(int fd,char *vptr,size_t n)
{
    size_t nread;
    size_t nleft;
    nread = 0;
    nleft = n;
    char *ptr = vptr;
    while(nleft > 0)
    {
        if((nread = read(fd,ptr,nleft)) < 0)
        {
            if(errno == EINTR)
                continue;
            else
                return -1;
        }
        else if(nread == 0)
        {
            break;
        }
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd,char *vptr,size_t n)
{
    size_t nwrite;
    size_t nleft;
    nwrite = 0;
    nleft = n;
    const char *ptr = vptr;
    while(nleft > 0)
    {
        if((nwrite = write(fd,ptr,nleft)) <= 0)
        {
            if(nwrite < 0 && errno == EINTR)
                continue;
            else
                return -1;
        }
        nleft -= nwrite;
        ptr += nwrite;
    }
    return (n - nleft);
}
