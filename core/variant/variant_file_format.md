Variant encoder standard. Version 001.
# File layout
+ Must be Little-endian encoded.
+ Must start with a string starting with "gncode" and the version the file is encoded as. Current version: "gncode001"
+ Must be encoded in UTF-8
+ Variant data starts at 0x09
## Variant encoding
Allowed types:
+ unknown (0x0)
+ bool (0x1)
+ unsigned 8 bit integer number (0x2)
+ signed 8 bit integer number (0x3)
+ unsigned 16 bit integer number (0x4)
+ signed 16 bit integer number (0x5)
+ unsigned 32 bit integer number (0x6)
+ signed 32 bit integer number (0x7)
+ unsigned 64 bit integer number (0x8)
+ signed 64 bit integer number (0x9)
+ IEEE-754 32 bit floating point number (0xA)
+ IEEE-754 64 bit floating point number (0xB)
+ String (0xC)
+ Vector2 with two IEEE-754 32 bit floating point numbers (0xD)
+ Vector2 with two IEEE-754 64 bit floating point number (0xE)
+ Vector2 with two signed 32 bit integer numbers (0xF)
+ Vector2 with two signed 64 bit integer numbers (0x10)
+ Rect2 with four IEEE-754 32 bit floating point numbers (0x11)
+ Rect2 with four IEEE-754 64 bit floating point number (0x12)
+ Rect2 with four signed 32 bit integer numbers (0x13)
+ Rect2 with four signed 64 bit integer numbers (0x14)
+ Transform2D with five 32 or 64 bit IEEE-754 floating point numbers (0x15)
+ Color8 with four unsigned 8 bit integer numbers (0x16)
+ Color16 with four unsigned 16 bit integer numbers (0x17)
+ Array with a generic type (0x18)

Allowed types must be encoded as a signed 16 bit integer number.
Certain types require their values to be stored in a specific way:
+ unknown must store its size in bytes at the beginning as an unsigned 64 bit integer number.
+ bool must be stored as a unsigned 8 bit integer number.
+ + if the value is not 0x0, the boolean is true, otherwise, false.
+ String must have its character count stored as an unsigned 64 bit integer number at 0x0.
+ Vector2 types must store their values in the following order:
+ + x
+ + y
+ Rect2 types must store their values in the following order:
+ + x
+ + y
+ + width
+ + height
+ Transform2D must store an unsigned 8 bit integer number at 0x0, indictating if its values are 32 bit or 64 bit floating point numbers.
+ + If the number does not equal 0x00, its floating pointer numbers are 64 bit, otherwise, 32 bit.
+ Transform2D must store its values at 0x1, in the following order:
+ + rotation in degrees
+ + origin x
+ + origin y
+ + scale x
+ + scale y
+ Color8 and Color16 must store its values in the following order:
+ + red
+ + green
+ + blue
+ + alpha
+ Array must have its element count stored at 0x0, as an unsigned 64 bit integer number.
## Storing variants
The type of the variant must be encoded as a signed 16 bit integer number right before the variant data.

## Notes
+ String is a specialization of Array
+ If the size on any Variant is not its actual size, the file is ill formed.
