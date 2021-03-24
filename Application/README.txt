Nanopb example "simple"
=======================

This example demonstrates the very basic use of nanopb. It encodes and
decodes a simple message.

The code uses four different API functions:

  * pb_ostream_from_buffer() to declare the output buffer that is to be used
  * pb_encode() to encode a message
  * pb_istream_from_buffer() to declare the input buffer that is to be used
  * pb_decode() to decode a message
