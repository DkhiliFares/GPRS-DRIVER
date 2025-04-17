# SIM808 GPRS Communication Library for STM32

## Overview

This project provides a library for communicating with the SIM808 module via UART on STM32 microcontrollers. It supports basic GPRS functionality including HTTP GET and POST requests, making it suitable for IoT applications that require internet connectivity.

## Features

- UART communication with SIM808 module
- HTTP GET and POST requests
- GPRS connection management
- Basic error handling
- STM32 HAL compatible

## Hardware Requirements

- STM32F4xx microcontroller
- SIM808 GSM/GPRS module
- UART connection between STM32 and SIM808 (typically 9600 baud)
- Power supply for both devices

## Software Requirements

- STM32CubeIDE or compatible toolchain
- STM32 HAL libraries
- Standard C libraries

## Installation

1. Clone this repository into your STM32 project directory
2. Include `gprs_lib.h` in your main application
3. Add `gprs_lib.c` to your project source files

## Usage

### Initialization

```c
#include "gprs_lib.h"

UART_HandleTypeDef huart1;  // Your UART handle

int main(void) {
    // Initialize HAL and system clocks
    HAL_Init();
    SystemClock_Config();
    
    // Initialize UART and GPIO
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    
    // Initialize SIM808 module
    if (SIM808_Init(&huart1) != 0) {
        printf("SIM808 initialization failed\n");
    } else {
        printf("SIM808 initialized successfully\n");
    }
    
    // ... rest of your application
}
```

### HTTP GET Request

```c
const char *url = "https://example.com/api";
char response[1024];

if (GPRS_HTTP_Get(&huart1, url, response) == 0) {
    printf("GET response: %s\n", response);
} else {
    printf("GET request failed\n");
}
```

### HTTP POST Request

```c
const char *url = "https://example.com/api";
const char *data = "key=value";
char response[1024];

if (GPRS_HTTP_Post(&huart1, url, data, response) == 0) {
    printf("POST response: %s\n", response);
} else {
    printf("POST request failed\n");
}
```

## Configuration

Modify the following in `gprs_lib.h` as needed:

```c
#define SIM808_RX_BUFFER_SIZE 1024  // Receive buffer size
#define SIM808_TX_BUFFER_SIZE 512   // Transmit buffer size
```

## Known Issues

- Fixed delay-based waiting for responses (could be improved with proper state machine)
- Limited error handling for network conditions
- APN is hardcoded to "orange.internet.org" (modify in `GPRS_HTTP_Get`/`GPRS_HTTP_Post`)

## Contributing

Contributions are welcome! Please open an issue or pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Example Output

```
Module SIM808 initialise avec succes
Reponse HTTP GET : +HTTPACTION: 0,200,15
OK
```

## Troubleshooting

1. **No response from module**:
   - Check power supply to SIM808
   - Verify UART connections (TX/RX crossed)
   - Confirm baud rate matches (default 9600)

2. **GPRS connection failures**:
   - Verify APN settings for your cellular provider
   - Check SIM card is properly inserted and has data plan

3. **HTTP request failures**:
   - Verify network coverage
   - Check URL is correct and accessible
