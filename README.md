### SysEx message format
|Byte|Description|
|---|---|
|F0|Start|
|7D|Manufacturer ID|
|6D|Further ID|
|64|Further ID|
|6C|Further ID|
|xx|Instruction|
|yy|Payload|
|...|...|
|cs|Checksum|
|F7|End|

Request Bank
F0 7D 6D 64 6C 00 01 cs F7
