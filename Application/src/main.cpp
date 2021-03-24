#include <predef.h>
#include <stdio.h>
#include <nbrtos.h>
#include <init.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

const char * AppName="protobuf";

void UserMain(void * pd)
{
    init();
    WaitForActiveNetwork(TICKS_PER_SECOND * 5);   // Wait up to 5 seconds for active network activity 

    iprintf("Application %s started\n",AppName );


    /* This is the buffer where we will store our message. */
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    /* Encode our message */
    {
        /* Allocate space on the stack to store the message data.
         *
         * Nanopb generates simple struct definitions for all the messages.
         * - check out the contents of simple.pb.h!
         * It is a good idea to always initialize your structures
         * so that you do not have garbage data from RAM in there.
         */
        SimpleMessage message = SimpleMessage_init_zero;

        /* Create a stream that will write to our buffer. */
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

        /* Fill in the lucky number */
        message.lucky_number = 13;

        /* Now we are ready to encode the message! */
        status = pb_encode(&stream, SimpleMessage_fields, &message);
        message_length = stream.bytes_written;

        /* Then just check for any errors.. */
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        }
    }

    /* Now we could transmit the message over network, store it in a file or
     * wrap it to a pigeon's leg.
     */

    /* But because we are lazy, we will just decode it immediately. */

    {
        /* Allocate space for the decoded message. */
        SimpleMessage message = SimpleMessage_init_zero;

        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

        /* Now we are ready to decode the message. */
        status = pb_decode(&stream, SimpleMessage_fields, &message);

        /* Check for errors... */
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        }

        /* Print the data contained in the message. */
        printf("Your lucky number was %d!\n", (int)message.lucky_number);
    }

    while (1)
    {
        OSTimeDly(TICKS_PER_SECOND);
    }
}
