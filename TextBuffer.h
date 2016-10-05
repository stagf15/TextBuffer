/*

  TextBuffer.h - Library for writing various types to a buffer
  that will store them in a char array of predetermined length
  
  Created by stagf15, 19 Jul 2016.
  Released into the public domain.
  
*/

#ifndef TextBuffer_h
#define TextBuffer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class TextBuffer
{
    
  public:
    
    // In general, functions will return the following:
    //    If failure, return int 0, or null terminator: (char)0
    //    If success, return int 1, or desired data
    
    // If malloc fails in begin() then it will return 0
    //   - all other functions will then return failure
    //   - if this is would cause failure in the sketch, recommend
    //       checking begin() for failure and handling there
    
    // Class to call to initialize the buffer (before Setup). Requires the 
    // desired size of the buffer in bytes. The size is then checked and 
    // converted, if required, to a multiple of 4. (for ESP8266 boards)
    TextBuffer(unsigned int bufSize);
    
    // Begins the buffer; allocates the memory (in Setup)
    int begin();
    
    // The following functions accept various types as input, but all write a 
    // string representation of that type to the buffer  
    
    // For each type, there is a write(bufData), which will write just the 
    // string, and a writeln(bufData), which will add a '\r\n' to the string 
    // to signify the end of a line
    
    int write(char* bufData);
    int writeln(char* bufData);
    int write(char bufData);
    int writeln(char bufData);
    int write(int bufData);
    int writeln(int bufData);
    int write(long unsigned int bufData);
    int writeln(long unsigned int bufData);
    int write(size_t bufData);
    int writeln(size_t bufData);
    int write(float bufData);
    int writeln(float bufData);
    int write(double bufData);
    int writeln(double bufData);
    int write(String bufData);
    int writeln(String bufData);
    int write();
    int writeln();
    int bufWrite(String bufData);
    String getCheckSum();
    
    // Clears the buffer, writes a null terminator to byte 0 and 
    // resets length and position to 0
    int clear();
    
    // Ends, or de-allocates the buffer and frees the memory   
    // Requires a begin() to use the buffer again
    int end();
    
    // Returns a pointer to the buffer as a const char array
    //   Used to return the buffer itself
    const char* getBuffer();
    
    // Returns a pointer to the buffer as a char array
    //   Used to modify the buffer directly from the calling sketch
    //   - this could be dangerous, if the capacity is not checked prior!
    //   - calling this will overwrite anything in the buffer
    char* getBufPointer();
    
    // Returns the size (length) of the buffer, not including null terminator
    int getSize();
    
    // Returns the capacity of the buffer, equal to the bufsize passed initially
    int getCapacity();
    
  private:  
  
    // Pointer to the buffer char array
    byte* buffer;
    
    // Variable to hold the aligned buffer max capacity
    //   - Aligned to multiples of 4 bytes for the ESP8266 boards
    unsigned int _bufSize;
    
    // Same as _bufSize, the max capacity, including null terminator, of the buffer
    unsigned int capacity;
    
    // The position of the "cursor", or reference point in the buffer (usually 0)
    unsigned int position;
    
    // Current length of the buffer content, NOT including the null terminator
    unsigned int length;
    
    // String used to temporarily store each individual input to the buffer
    String bufString;
    
    // The length of bufString, plus one for the null terminator
    unsigned int dataLen;
    
    // A char array, of length dataLen, to hold the bufString
    char tempBuf[];

};

#endif