stm32flash: invalid option -- '-'
Usage: stm32flash [-bvngfhc] [-[rw] filename] [tty_device | i2c_device]
    -a bus_address	Bus address (e.g. for I2C port)
    -b rate		Baud rate (default 57600)
    -m mode		Serial port mode (default 8e1)
    -r filename	Read flash to file (or - stdout)
    -w filename	Write flash from file (or - stdout)
    -C		Compute CRC of flash content
    -u		Disable the flash write-protection
    -j		Enable the flash read-protection
    -k		Disable the flash read-protection
    -o		Erase only
    -e n		Only erase n pages before writing the flash
    -v		Verify writes
    -n count	Retry failed writes up to count times (default 10)
    -g address	Start execution at specified address (0 = flash start)
    -S address[:length]	Specify start address and optionally length for
    read/write/erase operations
    -F RX_length[:TX_length]  Specify the max length of RX and TX frame
    -s start_page	Flash at specified page (0 = flash start)
    -f		Force binary parser
    -h		Show this help
    -c		Resume the connection (don't send initial INIT)
    *Baud rate must be kept the same as the first init*
    This is useful if the reset fails
    -R		Reset device at exit.
    -i GPIO_string	GPIO sequence to enter/exit bootloader mode
    GPIO_string=[entry_seq][:[exit_seq]]
    sequence=[[-]signal]&|,[sequence]

GPIO sequence:
    The following signals can appear in a sequence:
    Integer number representing GPIO pin
    'dtr', 'rts' or 'brk' representing serial port signal
    The sequence can use the following delimiters:
    ',' adds 100 ms delay between signals
    '&' adds no delay between signals
    The following modifiers can be prepended to a signal:
    '-' reset signal (low) instead of setting it (high)

Examples:
    Get device information:
    stm32flash /dev/ttyS0
    or:
    stm32flash /dev/i2c-0
    
        Write with verify and then start execution:
            stm32flash -w filename -v -g 0x0 /dev/ttyS0
    
        Read flash to file:
            stm32flash -r filename /dev/ttyS0
    
        Read 100 bytes of flash from 0x1000 to stdout:
            stm32flash -r - -S 0x1000:100 /dev/ttyS0
    
        Start execution:
            stm32flash -g 0x0 /dev/ttyS0
    
        GPIO sequence:
        - entry sequence: GPIO_3=low, GPIO_2=low, 100ms delay, GPIO_2=high
        - exit sequence: GPIO_3=high, GPIO_2=low, 300ms delay, GPIO_2=high
            stm32flash -i '-3&-2,2:3&-2,,,2' /dev/ttyS0
        GPIO sequence adding delay after port opening:
        - entry sequence: delay 500ms
        - exit sequence: rts=high, dtr=low, 300ms delay, GPIO_2=high
            stm32flash -R -i ',,,,,:rts&-dtr,,,2' /dev/ttyS0
