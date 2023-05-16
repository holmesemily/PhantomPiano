# Piano

C++ code to control a piano by operating servos on the various keys. Runs on a Raspberry Pi.
Key to GPIO combination has to be mapped in the program. Midi file to play can be chosen from directly via the command line.

This is based on the MidiParser made by MStefan99. Original repo available [here](https://github.com/MStefan99/Midi-Parser).  
___

## Usage
- You can compile the code with the command line `g++ *.cpp lib/*.cpp -lpthread -lpigpio -lstdc++fs`.
- And then execute it with `sudo ./a.out song_name file.mid [silent]`.

## C++ class requirements
- Multiple classes (Servos, Midi, Morceau)
- Inheritance (Morceau is derived from Midi)
- Exception (invalid GPIO pin number)
- Overloading operator (`<<` to display Servo information)
- STL Library usage (vector)

## Parameters
Variables can be modified at the top of the program.
- Change the number of connected servos via the servosNumber define.
- Change the lowest key by changing the baseIndex define.
- Change the mapping note to GPIO via the mappingNoteGPIO vector.
