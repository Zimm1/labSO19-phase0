#include "umps/libumps.h"
#include "umps/arch.h"
#include "../../libraries/disk/disk.h"
#include "../../libraries/terminal/terminal.h"
#include "../../utils/converter/converter_utils.h"
#include "../../utils/system/system_utils.h"

#define PARAMS_LENGTH               24

/*Number digits with string terminator (0)*/
#define CYLINDER_LENGTH             6
#define HEAD_SECT_LENGTH            4

/*Number digits without string terminator (0)*/
#define CYLINDER_NUMBER_DIGIT       5
#define HEAD_SECT_NUMBER_DIGIT      3

#define LINE_BUF_SIZE               256
#define DISK_READ_LENGTH            4096

#define RESET                       0
#define SEEK                        1
#define READ                        2
#define WRITE                       3
#define GEOMETRY                    4
#define EXIT                        5

static int cmd;

static int get_cmd(char* c){
    char my_chr = c[0];
    if(IS_DIGIT(my_chr)){
        return my_chr - '0';
    }
    return -1;
}

int main(int argc, char *argv[]){

	term_puts("****************************************************\n");
    term_puts("             Reading/Writing on DISK                \n");
    term_puts("****************************************************\n");

    do{

        char my_cmd[LINE_BUF_SIZE];

        term_puts("0: reset\n");
        term_puts("1: seek\n");
        term_puts("2: read\n");
        term_puts("3: write\n");
        term_puts("4: show disk geometry\n");
        term_puts("5: exit\n");

        term_putchar('\n');

        term_puts("Insert cmd: ");

        readline(my_cmd,LINE_BUF_SIZE);

        /*Take the first character from the line read and cast it to integer if possible*/
        cmd = get_cmd(my_cmd);

        term_putchar('\n');

        switch(cmd){

            case RESET: {
                term_puts("Resetting...\n");
                int res = reset();
                if(res == ST_DEVICE_READY){
                    term_puts("\nReset completed!\n");
                } else {
                    term_puts(show_error_message(res));
                }
                break;
            }

            case SEEK: {

                char buf[LINE_BUF_SIZE];

                term_puts("Insert cylinder number: ");
                readline(buf,PARAMS_LENGTH);

                /*Cast the first CYLINDER_NUMBER_DIGIT characters to integer*/
                int cyl = get_int(buf, CYLINDER_NUMBER_DIGIT);

                if(cyl != -1){
                    int res = seek(cyl);
                    if(res == ST_DEVICE_READY){
                        term_puts("Seek completed!\n");
                    } else {
                        term_puts(show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case READ: {

                char buf[LINE_BUF_SIZE];

                term_puts("Insert sector: ");
                readline(buf,PARAMS_LENGTH);

                /*Cast the first HEAD_SECT_NUMBER_DIGIT characters to integer*/
                int sect = get_int(buf,HEAD_SECT_NUMBER_DIGIT);

                term_puts("\nInsert head: ");
                readline(buf,PARAMS_LENGTH);

                int head = get_int(buf,HEAD_SECT_NUMBER_DIGIT);

                if(sect != -1 && head != -1){
                    char text_read[DISK_READ_LENGTH];

                    int res = disk_read(text_read,sect,head);
                    if(res == ST_DEVICE_READY){
                        term_puts("\nRead completed!\n\n");
                        term_puts(text_read);
                        term_putchar('\n');
                    } else {
                        term_puts(show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case WRITE: {

                char buf[LINE_BUF_SIZE];

                term_puts("Insert sector: ");
                readline(buf,PARAMS_LENGTH);
                int sect = get_int(buf,HEAD_SECT_NUMBER_DIGIT);

                term_puts("\nInsert head: ");
                readline(buf,PARAMS_LENGTH);
                int head = get_int(buf,HEAD_SECT_NUMBER_DIGIT);

                if(sect != -1 && head != -1){
                    char text_write[LINE_BUF_SIZE];
                    term_puts("\n\nWrite something....\n\n");
                    readline(text_write,LINE_BUF_SIZE);

                    int res = disk_write(text_write,sect,head);

                    if(res == ST_DEVICE_READY){
                        term_puts("\nText written in the disk!\n");
                    } else {
                        term_puts(show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case GEOMETRY: {

                term_puts("MAX CYLINDER ");
                int max_cyl = get_maxcyl();
                term_puts(itoa(max_cyl,CYLINDER_LENGTH));

                term_puts("\nMAX SECTOR ");
                int max_sect = get_maxsect();
                term_puts(itoa(max_sect,HEAD_SECT_LENGTH));

                term_puts("\nMAX HEAD ");
                int max_head = get_maxhead();
                term_puts(itoa(max_head,HEAD_SECT_LENGTH));
                term_putchar('\n');

                break;
            }

            case EXIT: {
                break;
            }

            default:{
                term_puts("\nInvalid command!\n\n");
                break;
            }
        }

        term_putchar('\n');

    } while (cmd != EXIT);

    term_puts("****************************************************\n");
    term_puts("                 Disk test completed                \n");
    term_puts("****************************************************\n");

    halt();

	return 0;
}