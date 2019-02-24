#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main( int argc, char ** argv )
{
    if( argc != 3 )
    {
        fprintf( stderr, "Usage: %s file typename\n", argv[0] );
        return EXIT_FAILURE;
    }

    struct stat st;
    if( stat( argv[1], &st ) < 0 )
    {
        fprintf( stderr, "Failed to open file '%s': %s\n", argv[1], strerror( errno ) );
        return EXIT_FAILURE;
    }

    int fd = open( argv[1], 0 );
    if( fd < 0 )
    {
        fprintf( stderr, "Failed to open file '%s': %s\n", argv[1], strerror( errno ) );
        return EXIT_FAILURE;
    }

    unsigned char * buf = malloc( (size_t)st.st_size );
    read( fd, buf, (size_t)st.st_size );

    printf( "static const u8 %s[%ld] = {", argv[2], st.st_size );
    for( int i = 0; i < st.st_size; i++ )
    {
        printf( "%d", buf[i] );
        if( i != st.st_size - 1 )
            printf( "," );
    }
    printf( "};\n" );

    close( fd );
    free( buf );
}

