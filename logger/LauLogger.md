# LAutopin Logger
LauLogger is a module of LAutopin, designed for recording files for LAutopin
monitoring.

## Data Layout
* **Endianness**
Data is stored in Little Endian.
* **Data Format**
Data format is:
Timestamp: unsigned long, 8 bytes
Id: 1 byte
Length: 1 byte
Payload: up to 255 bytes, optional User-Choosen Endianness.
* **Graphical Representation**:  
Time Stamp | ID | Length | Payload
---|---|---|---
8B | 1B | 1B | (flex)
