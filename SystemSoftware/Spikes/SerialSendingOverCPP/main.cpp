/*Código original por Geoffrey Hunter; tomado del enlace https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/, y originalmente licenciado bajo CC-BY 4.0. https://creativecommons.org/licenses/by/4.0/*/

// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int serial_port = open("/dev/ttyUSB0", O_RDWR);
struct termios tty;
unsigned char msg[] = { 'H', 'e', 'l', 'l', 'o', '\r' };
const char * message_2 = "test_2\n";
const char * message_3 = "exit\n";
char read_buf [256];

int main() {
    // Check for errors
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return 1;
    }
    
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all the size bits, then use one of the statements below
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag |= ICANON; // Detect \n to read.     
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }
    
   /*
   tty.c_lflag |= ICANON;
   cfsetispeed(&tty, B115200);
   cfsetospeed(&tty, B115200);
   if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }
    */
    while (1) {
        int num_bytes = write(serial_port, &msg, sizeof(msg));
        //printf("Sent %i bytes. Sent message: %s\n", num_bytes, msg);
        int num_bytes_read = read(serial_port, &read_buf, sizeof(read_buf));
        if (num_bytes_read < 0) {
            printf("Error reading: %s", strerror(errno));
            return 1;
        }
        printf("Read %i bytes. Received message: %s\n", num_bytes_read, read_buf);
        //int num_bytes_2 = write(serial_port, &message_3, strlen(message_3));
        //printf("Sent %i bytes. Sent message: %s\n", num_bytes_2, message_3);
        //int num_bytes_3 = write(serial_port, &message_2, strlen(message_2));
        //printf("Sent %i bytes. Sent message: %s\n", num_bytes_3, message_2);
        //int num_bytes_4 = write(serial_port, &message_3, strlen(message_3));
        //printf("Sent %i bytes. Sent message: %s\n", num_bytes_4, message_3);
    }
    close(serial_port);
    return 0; // success
}
