#include "umps/libumps.h"
#include "umps/arch.h"
#include "../../libraries/disk/disk.h"
#include "../../libraries/terminal/terminal.h"
#include "../../utils/converter/converter_utils.h"
#include "../../utils/system/system_utils.h"

#define LINE_LENGTH                 24
#define CMD_LENGTH                  1

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

        term_readline(my_cmd, LINE_BUF_SIZE);

        /*Take the first character from the line read and cast it to integer if possible*/
        cmd = str_to_int(my_cmd, CMD_LENGTH, 10);

        term_putchar('\n');

        switch(cmd){

            case RESET: {
                term_puts("Resetting...\n");
                int res = disk_reset();
                if(res == ST_DEVICE_READY){
                    term_puts("\nReset completed!\n");
                } else {
                    term_puts(disk_show_error_message(res));
                }
                break;
            }

            case SEEK: {
                char buf[LINE_BUF_SIZE];

                term_puts("Insert cylinder number: ");
                term_readline(buf, LINE_LENGTH);

                /*Cast the first CYLINDER_NUMBER_DIGIT characters to integer*/
                int cyl = str_to_int(buf, CYLINDER_NUMBER_DIGIT, 10);

                if(cyl != -1){
                    int res = disk_seek(cyl);
                    if(res == ST_DEVICE_READY){
                        term_puts("Seek completed!\n");
                    } else {
                        term_puts(disk_show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case READ: {
                char buf[LINE_BUF_SIZE];

                term_puts("Insert sector: ");
                term_readline(buf, LINE_LENGTH);

                /*Cast the first HEAD_SECT_NUMBER_DIGIT characters to integer*/
                int sect = str_to_int(buf, HEAD_SECT_NUMBER_DIGIT, 10);

                term_puts("\nInsert head: ");
                term_readline(buf, LINE_LENGTH);

                int head = str_to_int(buf, HEAD_SECT_NUMBER_DIGIT, 10);

                if(sect != -1 && head != -1){
                    char text_read[DISK_READ_LENGTH];

                    int res = disk_read(text_read, sect, head);
                    if(res == ST_DEVICE_READY){
                        term_puts("\nRead completed!\n\n");
                        term_puts(text_read);
                        term_putchar('\n');
                    } else {
                        term_puts(disk_show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case WRITE: {
                char buf[LINE_BUF_SIZE];

                term_puts("Insert sector: ");
                term_readline(buf,LINE_LENGTH);
                int sect = str_to_int(buf, HEAD_SECT_NUMBER_DIGIT, 10);

                term_puts("\nInsert head: ");
                term_readline(buf,LINE_LENGTH);
                int head = str_to_int(buf, HEAD_SECT_NUMBER_DIGIT, 10);

                if(sect != -1 && head != -1){
                    char text_write[LINE_BUF_SIZE];
                    term_puts("\n\nWrite something....\n\n");
                    term_readline(text_write, LINE_BUF_SIZE);

                    int res = disk_write(text_write, sect, head);

                    if(res == ST_DEVICE_READY){
                        term_puts("\nText written in the disk!\n");
                    } else {
                        term_puts(disk_show_error_message(res));
                    }
                } else {
                    term_puts("\nInvalid input!\n\n");
                }

                break;
            }

            case GEOMETRY: {
                term_puts("MAX CYLINDER ");
                int max_cyl = disk_get_maxcyl();
                term_puts(int_to_str(max_cyl, CYLINDER_LENGTH));

                term_puts("\nMAX SECTOR ");
                int max_sect = disk_get_maxsect();
                term_puts(int_to_str(max_sect, HEAD_SECT_LENGTH));

                term_puts("\nMAX HEAD ");
                int max_head = disk_get_maxhead();
                term_puts(int_to_str(max_head, HEAD_SECT_LENGTH));
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