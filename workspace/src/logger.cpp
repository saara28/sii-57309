#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];

    // borrar FIFO por si existiera previamente
    unlink("/tmp/fifo_tenis");

    /* crear el FIFO */
    if (mkfifo("/tmp/fifo_tenis", 0666)<0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    fd = open("/tmp/fifo_tenis", O_RDONLY);
    
    
    if (fd<0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    /* Leer de la FIFO */
   int leidos;
    while ((leidos = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[leidos] = '\0';
        printf("%s", buffer);
    }
    
    close(fd);
    unlink("/tmp/fifo_tenis"); // Elimina la tubería FIFO del sistema de archivos
    
    return(0);
}
