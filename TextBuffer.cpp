#include "Arduino.h"
#include "TextBuffer.h"

TextBuffer::TextBuffer(unsigned int bufSize)
  {
    _bufSize = (bufSize + 3) & (~3);  // Makes sure it's a multiple of 4
                                      //   - required for the ESP8266 boards
    //begin();                        // Automatically call the begin fuction
                                      //   - not used
  }

int TextBuffer::begin()
  {
    buffer = (byte*)malloc(sizeof(byte)*_bufSize);
    
    if (!buffer) return 0;            // return failure if malloc fails
    
    buffer[0] = (char)0;              // Initialize first byte as null terminator
    capacity = _bufSize;
    position = 0;
    length = 0;                       // Length does not include null terminator
    return 1;                         // return success
  }

int TextBuffer::write(char* bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(char* bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(char bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(char bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(int bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(int bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(long unsigned int bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(long unsigned int bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(size_t bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(size_t bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(float bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(float bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(double bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(double bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write(String bufData)
  {
    String bufString = String(bufData);
    return bufWrite(bufString);
  }

int TextBuffer::writeln(String bufData)
  {
    String bufString = String(bufData)  + "\r\n";
    return bufWrite(bufString);
  }

int TextBuffer::write()
  {
    return bufWrite("");
  }

int TextBuffer::writeln()
  {
    return bufWrite("\r\n");
  }

int TextBuffer::bufWrite(String bufString)
  {
    unsigned int dataLen = bufString.length() + 1;
    char tempBuf[dataLen];
    
    bufString.toCharArray(tempBuf, dataLen);
    
    if((length + dataLen) < capacity)
      {
        for (int bt = 0; bt < (dataLen); bt++)
          {
            // save each data byte to the end of the buffer
            buffer[((position+length) % capacity)] = tempBuf[bt];
            // increment the length unless it's the last byte (null terminator)
            if (bt != (dataLen - 1)) length++;
          }
        return 1;                 // return success
      }
    return 0;                     // return failure
  }
  
int TextBuffer::clear() 
  {
    if (!buffer) return 0;        // return failure
    buffer[0] = (char)0;
    position = 0;
    length = 0;
    return 1;                     // return success
  } 

int TextBuffer::end()
  {
    if (!buffer) return 0;        // return failure
    free(buffer);
    return 1;                     // return success
  }

const char* TextBuffer::getBuffer() 
  {
    if (!buffer) return (char)0;  // return null terminator
    return (const char*)buffer;   // return const char array buffer pointer
  }
  
char* TextBuffer::getBufPointer() 
  {
    if (!buffer) return 0;        // return failure
    clear();                      // clear the buffer
    return (char*)buffer;         // return char array buffer pointer
  }
  
int TextBuffer::getSize()
  {
    if (!buffer) return 0;        // return failure
      if (strlen((const char*)buffer) != length)
        // if the length is not correct, probably due to an external
        // write to the buffer, reset it to the correct length
        {
          length = strlen((const char*)buffer);
        }
    return length;
  }

int TextBuffer::getCapacity()
  {
    if (!buffer) return 0;        // return failure
    return capacity;
  }
  
String TextBuffer::getCheckSum()
  {
    // Create Checksum
    char checkSum = 0;
    int csCount = 1;
    while (buffer[csCount + 1] != 0)
    {
      checkSum ^= buffer[csCount];
      csCount++;
    }
    // Change the checksum to a string, in HEX form, convert to upper case, and print
    String checkSumStr = String(checkSum, HEX);
    checkSumStr.toUpperCase();
    
    return checkSumStr;
  }