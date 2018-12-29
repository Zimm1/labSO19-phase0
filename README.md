# project-arrow

# Disk Library

Library that allows to use the disk avoiding the direct interaction with disk register. <br>
In this way the programmer doesn't need to manually load the memory address in DATA0 (necessary for the I/O operations) and create
the right COMMAND for each operations. 

## Disk I/O

*	```int disk_read(void* address,unsigned int sectnum, unsigned int headnum)``` <br>
			Read the block located at (sectnum, headnum) in the current cylinder and copy it into RAM starting at (address).

* 	```int disk_write(void* address,unsigned int sectnum, unsigned int headnum)``` <br>
			Copy the 4K of RAM starting at (address) and write it into block located at (sectnum, headnum) in the current cylinder.

* 	```int reset()``` <br>
			Move the boom to cylinder 0.

* 	```int seek(unsigned int cyl)``` <br>
			Move the boom to cylinder (cyl).

All this functions return the value of ST_DEVICE_READY if the operation ends without error, otherwise return the value of error.

## Disk geometry

The field name DATA1 describes the physical characteristics of the disk's geometry. <br>
The following functions allow to get directly the value of interested field (cylinder, sector, head) without any additional operations
on value in DATA1. 

* 	```int get_maxcyl()``` <br>
			Returns the number of cylinders.

* 	```int get_maxsect()``` <br>
			Returns the number of sectors.

* 	```int get_maxhead()``` <br>
			Returns the number of heads.

## Coordinates (cylinder, head, sector) checker

The following functions check if the coordinates have a valid value.

* 	```bool check(unsigned int sect, unsigned int head)``` <br>
			Returns true only if the values of (sect, head) are respectively lesser of (MAXSECT, MAXHEAD) and major of 0.

* 	```bool check_sect(unsigned int sect)``` <br>
			Returns true only if the value of (sect) is lesser of (MAXSECT) and major of 0.

* 	```bool check_head(unsigned int head)``` <br>
			Returns true only if the value of (head) is lesser of (MAXHEAD) and major of 0.

* 	```bool check_cyl(unsigned int cyl)```  <br>
			Returns true only if the value of (cyl) is lesser of (MAXCYL) and major of 0.

## Text error

* 	```char* show_error_message(unsigned int error)``` <br>
			Returns the text error of a given number (error).

## How to create a new disk

```umps2-mkdev -d <diskfile.umps> [parameters]``` 

* <b>-d</b> flag that indicates the creation of a disk.

* <b><diskfile.umps></b> disk file name.

* <b>[parameters]</b> parameters are necessaries only for the creation of a custom disk device (see the doc of umps2-mkdev for more details).