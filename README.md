# labSO 2018-2019 - Phase 0
Libraries and examples for network and disk uMPS interfaces.

## Network
uMPS network interface is made for VDE (Virtual Distributed Network), a virtual network framework.

### Setup
* Install VDE with the method you prefer (for example APT)
    ```
    sudo apt install vde2
    ```
* Create and run a new switch
    ```
    vde_switch -s /tmp/switch1
    ```
* Create a symbolic link to the switch
    ```
    ln -s /tmp/switch1 net0.umps
    ```
* In uMPS, load / create a virtual machine and set `net0.umps` as the configuration file for the first network interface
* Start the virtual machine, which will now be connected to the switch created earlier
* In order to exchange messages between VMs, open different uMPS instances and connect them to the same switch

### Network Library
It allows the programmer to use a uMPS network interface without a direct manipulation of its register.

##### Network communication
*	`int net_read(packet_t *packet)`<br>
			Reads a pending received packet, if any, to (packet)

* 	`int net_write(packet_t *packet, unsigned int length)`<br>
			Sends a (packet) containing a message which is long (length) chars
            
These functions return -1 in case of an error, the message length otherwise
            
##### Network configuration
*	`int net_conf_read(net_conf_t* conf)`<br>
			Reads the current network interface configuration to (conf)

* 	`int net_conf_write(net_conf_t* conf)`<br>
			Sets the network interface configuration to (conf)
            
* 	`int net_conf_set_promisq(unsigned int mode)`<br>
			Sets the current interface ability to intercept all packets on the network
           
* 	`int net_reset()`<br>
			Empties the read and write buffers, resets the network address to default
            
These functions return -1 if in case of an error, 0 otherwise

## Disk
In uMPS, the disk is an external file which can be read and written and is divided in 4 KB blocks, indexed by cylinders, heads and sectors.

### Setup
* Create a new disk
    ```
    umps2-mkdev -d disk0.umps
    ``` 

* In uMPS, load / create a virtual machine and set `disk0.umps` as the configuration file for the first disk interface

### Disk Library
It allows the programmer to use a uMPS disk interface without a direct manipulation of its register.

##### Disk I/O
*	`int disk_read(void* address,unsigned int sectnum, unsigned int headnum)`<br>
			Reads the block located at (sectnum, headnum) in the current cylinder and copies it to the RAM starting at (address)

* 	`int disk_write(void* address,unsigned int sectnum, unsigned int headnum)`<br>
			Copies 4 KB of RAM starting at (address) and writes to the block located at (sectnum, headnum) in the current cylinder

* 	`int reset()`<br>
			Moves the boom to cylinder 0

* 	`int seek(unsigned int cyl)`<br>
			Moves the boom to cylinder (cyl)

These functions return the value of ST_DEVICE_READY if the operation ends without errors, the id of the error otherwise.

##### Disk geometry
* 	`int get_maxcyl()`<br>
			Returns the number of cylinders

* 	`int get_maxsect()`<br>
			Returns the number of sectors

* 	`int get_maxhead()`<br>
			Returns the number of heads

##### Coordinates (cylinder, head, sector) checker
* 	`bool check(unsigned int sect, unsigned int head)`<br>
			Returns true only if the values of (sect, head) are respectively lesser then (MAXSECT, MAXHEAD) and greater than 0

* 	`bool check_sect(unsigned int sect)`<br>
			Returns true only if the value of (sect) is lesser than (MAXSECT) and greater than 0

* 	`bool check_head(unsigned int head)`<br>
			Returns true only if the value of (head) is lesser than (MAXHEAD) and greater than 0

* 	`bool check_cyl(unsigned int cyl)`<br>
			Returns true only if the value of (cyl) is lesser than (MAXCYL) and greater than 0

##### Text error
* 	`char* show_error_message(unsigned int error)`<br>
			Returns the error message for a given error id (error)
