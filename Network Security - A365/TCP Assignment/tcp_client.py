# author @Quinton Odenthal
# email quintonodenthal@gmail.com
# last update 10/16/2022
# File that builds and packs a TCP packet. The __init__ and to_bytes methods are
# code from Dr. Shawn Butler's Network class

import argparse
import time
from socket import AF_INET, SOCK_DGRAM, timeout
import socket
from TCPMachine import *
from TCPSegment import *
from SelectiveRepeat import *
from bitstring import Bits, BitArray
from Functions import *

# Parses command line for arguments
parser = argparse.ArgumentParser(description='Processes input for TCP')
parser.add_argument('-a', "--address", required=True, type=str, help='An IP address for your desired connection')
parser.add_argument('-cp', "--clientport", required=True, type=int, help='Port number for your desired connection')
parser.add_argument('-f', "--filename", required=True, type=str, help='Filename of reqested file')
parser.add_argument('-sp', "--serverport", required=True,
                    type=int, help='Server port number for your desired connection')
parser.add_argument('-m', "--mode", required=True, type=str, help='Desired mode: write (w), or read (r)')
args = parser.parse_args()

# Tests commandline inputs

if args.mode != 'w' and args.mode != 'r':
    print("Invalid value for 'mode' flag. Must use 'r' (read) or 'w' (write) \n" + "Please try again.")
    exit()
elif args.clientport < 5000 or args.clientport > 65535 or args.serverport < 5000 or args.serverport > 65535:
    print("Port range is restricted to between 5000 and 65535, inclusive \n" + "Please try again")
    exit()

print("Arguments:")
print("Address: ", args.address)
print("Client port: ", args.clientport)
print("Filename: ", args.filename)
print("Server port: ", args.serverport)
print("Mode: ", args.mode)

# Creates TCP socket with command inputs

clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.bind(("", args.clientport))
clientSocket.connect((args.address, args.serverport))
clientSocket.settimeout(4)

MAX_RECV_ATTEMPTS = 6
REC_WINDOW_SIZE = 1452*6
MAX_DATA_LEN = 1452

if __name__ == '__main__':
    # 3-way handshake

    tcp_machine = TCPMachine()

    create_tcb()
    # Set client sequence num to random valid seq_num
    sequence_num = get_random_seq_num()
    # Create SYN packet with new seq_num
    syn_packet = make_packet(pack_type="syn", seq_num=sequence_num, ack_num=0, arguments=args, window=REC_WINDOW_SIZE)
    # Send SYN packet
    send(syn_packet, clientSocket)
    # Increment sequence number because syn packet consumes 1 byte
    sequence_num += 1

    tcp_machine.active_open()  # Now in SYN sent state

    # Receive packet and turns incoming bytes message into TCPSegment object
    incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)

    # Loop for receiving valid (syn,ack), or syn packet
    while True:
        # Received syn,ack packet
        if incoming_packet.get_type() == "syn,ack":

            # Incoming syn,ack has unexpected ack_num
            if incoming_packet.ack_num != syn_packet.exp_ack_num:

                # Gets new received packet, resends syn packet on timeout
                incoming_packet = rec_resend_pack(syn_packet, clientSocket)

            # Incoming syn,ack packet has expected ack num
            else:
                window = incoming_packet.window
                # Set acknowledge number to incoming seq num + size of syn packet (1 byte)
                acknowledge_num = incoming_packet.seq_num + 1
                # Create ack packet for incoming syn packet
                ack_packet = make_packet(pack_type="ack", seq_num=sequence_num, ack_num=acknowledge_num,
                                         arguments=args,
                                         window=window)
                # Increment seq_num by 1 for empty ack
                # sequence_num += 1
                print("Sending ack for received syn,ack packet")
                # Send ack for incoming syn
                send(ack_packet, clientSocket)
                # Transition to ESTAB state
                tcp_machine.rcv_synack()
                break  # Leave loop

        # Received syn packet
        elif incoming_packet.get_type() == "syn":
            window = incoming_packet.window
            # Set acknowledge number to incoming seq num + size of syn packet (1 byte)
            acknowledge_num = incoming_packet.seq_num + 1
            # Create ack packet for incoming syn packet
            ack_packet = make_packet(pack_type="ack", seq_num=sequence_num, ack_num=acknowledge_num,
                                     arguments=args, window=window)
            # Increment seq_num by 1 for empty ack
            sequence_num += 1
            # Send ack for incoming syn
            send(ack_packet, clientSocket)
            # Transition to SYN Received state
            tcp_machine.rcv_syn()
            break  # Leave loop

        # Packet is not of expected type
        else:

            # Gets new received packet, resends syn packet on receive timeout
            incoming_packet = rec_resend_pack(syn_packet, clientSocket)

            pass  # Loop through and check next received packet

    # If we are in state syn received, wait for ack of syn
    if tcp_machine.is_syn_rcvd:
        # Receive packet and turns incoming bytes message into TCPSegment object
        incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)

        while True:
            # Received ack packet
            if incoming_packet.get_type() == "ack":

                # Incoming ack has unexpected ack_num
                if incoming_packet.ack_num != syn_packet.exp_ack_num:

                    # Gets new received packet, resends syn packet on receive timeout
                    incoming_packet = rec_resend_pack(syn_packet, clientSocket)

                # Incoming ack packet has expected ack num
                else:
                    print("Received ack of syn, transitioning to estab state")
                    # Transition to ESTAB state
                    tcp_machine.rcv_ack_of_syn()
                    break  # Leave loop

            # Received repeat syn packet
            elif incoming_packet.get_type() == "syn":
                print("Received repeat syn packet, resending ack")
                # Resend ack for incoming syn
                send(ack_packet, clientSocket)

            # Received packet of unexpected type
            else:

                # Gets new received packet, resends syn packet on receive timeout
                incoming_packet = rec_resend_pack(syn_packet, clientSocket)
                pass  # Loop through and attempt to receive packet again

    # 3-way handshake complete
    print("3-way handshake complete")

    # In ESTAB state, ready to send and receive data
    if tcp_machine.is_estab:
        print("Entering ESTAB state")

        # Check if read or write mode

        # If write mode
        if args.mode == "w":
            print("Write mode")

            # Create selective repeat object to store send and receive windows
            print("Creating selective repeat object")
            send_window_size = incoming_packet.window  # Size of send window
            sr_machine = SelectiveRepeat(filename=args.filename, source_port=args.clientport, dest_port=args.serverport,
                                         wnd_size=send_window_size, seq_num=sequence_num, ack_num=acknowledge_num,
                                         address=args.address, rec_wnd_size=window, state_machine=tcp_machine)

            # Making first data packet, also an ack
            data_iter = 0  # Pointer to first piece of new data to be read
            try:
                print("Trying to read data from file to make first data,ack packet")
                # Computes amount of data that should be read and sent in packet
                # Space in sent window exceeds max data length
                if sr_machine.remaining_space_in_sent_window() > MAX_DATA_LEN:
                    data_len = MAX_DATA_LEN
                # Space in sent window is <= max data length
                else:
                    data_len = sr_machine.remaining_space_in_sent_window()
                # Reads data from file, updates data_iter
                data, data_iter = read_out(args.filename, data_start=data_iter, data_len=data_len)

                # If EOF
                if len(data) == 0:
                    print("Read data with length 0, EOF")
                    raise EOFError

                # Makes new packet object with read data
                data_segment = TCPSegment(data=data, source_port=args.clientport, dest_port=args.serverport,
                                          seq_num=sequence_num,
                                          ack_num=acknowledge_num, window=window)
                # Updates seq_num to seq_num + len(data)
                sequence_num += len(data)
                # Sets packet as an ACK packet
                data_segment.build_ACK_packet()
                # Sends packet
                send(data_segment, clientSocket)
                # Adds packet to sent window
                sr_machine.add_pack_to_sent_window(data_segment)
                print("Successfully created first ack with data")
                print("Seq_num: ", data_segment.seq_num, " and Ack_num: ", data_segment.ack_num)
            # End Of File has been reached, file is empty, send Ack with no data
            except EOFError:
                print("EOF Error received, first packet has no data, sending ack with no data:")
                # Makes new packet object with read data
                ack_packet = make_packet("ack", seq_num=sequence_num, ack_num=acknowledge_num, window=window,
                                         arguments=args)
                # Updates seq_num
                sequence_num += 1
                # Sends packet
                send(ack_packet, clientSocket)
                print("Seq_num: ", ack_packet.seq_num, " and Ack_num: ", ack_packet.ack_num)
                pass

            # Still in ESTAB, continue to make and send data packets
            if tcp_machine.is_estab:
                # Loop to fill sent window with data packets
                while True:
                    # If read_out raises EOF Error, end of file has been reached, stop adding packets to windows
                    try:
                        print("Attempting to read data to make packets for sent window")
                        # Computes amount of data that should be read and sent in packet
                        # Space in sent window exceeds max data length
                        if sr_machine.remaining_space_in_sent_window() > MAX_DATA_LEN:
                            data_len = MAX_DATA_LEN
                        # Space in sent window is <= max data length
                        else:
                            data_len = sr_machine.remaining_space_in_sent_window()
                        # Reads data from file
                        data, data_iter = read_out(args.filename, data_start=data_iter, data_len=data_len)

                        # If EOF
                        if len(data) == 0:
                            print("Read data with length 0, EOF")
                            break

                        # Makes new packet object with read data
                        data_segment = TCPSegment(data=data, source_port=args.clientport, dest_port=args.serverport,
                                                  seq_num=sequence_num,
                                                  ack_num=acknowledge_num, window=window)
                        # Updates seq_num to seq_num + len(data)
                        sequence_num += len(data)
                        # Sends packet
                        send(data_segment, clientSocket)
                        # Adds packet to sent window
                        sr_machine.add_pack_to_sent_window(data_segment)
                        print("Successfully created data packet for sent window")
                        print("Seq_num: ", data_segment.seq_num, " and Ack_num: ", data_segment.ack_num)
                    # End Of File has been reached, send FIN, go to FIN-Wait-1
                    except EOFError:
                        print("Received EOF ERROR")
                        # Make fin packet
                        # fin_packet = make_packet("fin", ack_num=sr_machine.ack_num, seq_num=sr_machine.seq_num,
                        #                          arguments=args,
                        #                          window=sr_machine.window_size)
                        # # Send FIN packet
                        # send(fin_packet, clientSocket)
                        # # # Add FIN packet to sent window
                        # # add_pack_to_windows(sr_machine, fin_packet, clientSocket)
                        # tcp_machine.close()
                        break

                    # If sent window is full
                    if sr_machine.check_if_sent_window_full():
                        break

            # Still in ESTAB, continue to make data packets
            if tcp_machine.is_estab:
                # Loop to fill to-be-sent window with data packets
                while True:
                    # If read_out raises EOF Error, end of file has been reached, stop adding packets to windows
                    try:
                        print("Attempting to make data packet to fill to-be-sent window")
                        # Computes amount of data that should be read in packet
                        # Space in to-be-sent window exceeds max data length
                        if sr_machine.remaining_space_in_to_be_sent_window() > MAX_DATA_LEN:
                            data_len = MAX_DATA_LEN
                        # Space in to-be-sent window is <= max data length
                        else:
                            data_len = sr_machine.remaining_space_in_to_be_sent_window()
                        # Reads data from file
                        data, data_iter = read_out(args.filename, data_start=data_iter, data_len=data_len)

                        # If EOF
                        print("Read data length: ", len(data))
                        if len(data) == 0:
                            print("Read data with length 0, EOF")
                            break

                        # Makes new packet object with read data
                        data_segment = TCPSegment(data=data, source_port=args.clientport, dest_port=args.serverport, seq_num=sequence_num,
                                             ack_num=acknowledge_num, window=window)
                        # Updates seq_num to seq_num + len(data)
                        sequence_num += len(data)
                        # Adds packet to to-be-sent window
                        sr_machine.add_pack_to_to_be_sent_window(data_segment)
                        print("Successfully created data packet for to-be-sent window")
                        print("Seq_num: ", data_segment.seq_num, " and Ack_num: ", data_segment.ack_num)

                    # End Of File has been reached, must wait until all data
                    # packets have been sent before going to FIN-Wait-1
                    except EOFError:
                        print("Received EOF ERROR")
                        # # Make fin packet
                        # fin_packet = make_packet("fin", ack_num=sr_machine.ack_num, seq_num=sr_machine.seq_num, arguments=args,
                        #                          window=sr_machine.window_size)
                        # # Add FIN packet to to-be-sent window
                        # add_pack_to_windows(sr_machine, fin_packet, clientSocket)
                        break

                    # If to-be-sent window is full
                    if sr_machine.check_if_to_be_sent_window_full():
                        break

            # Selective repeat will continue to make data packets until EOF has been reached
            # It will then stop making packets and wait until all created packets have been sent
            # When all packets have been sent (sent window is empty) it will transition to Fin-Wait-1 state

            # Selective repeat protocol in effect
            while tcp_machine.is_estab:
                incoming_packet = rec_pack(clientSocket, depth=MAX_RECV_ATTEMPTS)

                # If incoming packet is ACK, check ack_num, acknowledge received data, send more data packets if possible
                if incoming_packet.get_type() == "ack":
                    print("Received ack packet")
                    # If received ack_num applies to packet in sent window
                    if check_valid_ack(sr_machine, incoming_packet.ack_num):
                        print("Received ack packet is valid")
                        # Acks packet with seq_num + len(data) == incoming ack_num
                        ack_pack_in_list(sr_machine, incoming_packet.ack_num)
                        # Shifts out acked packets in sent window to make room for new packets
                        sr_machine.shift_out_acked_packets()

                        # Shift packets from to-be-sent window into sent window and sends them
                        shift_to_be_sent_into_sent(sr_machine, clientSocket)
                        # Try to read data from file to make more data packets
                        while True:
                            # If to-be-sent window is full
                            if sr_machine.check_if_to_be_sent_window_full():
                                # Don't make any packets
                                break

                            # If read_out raises EOF Error, end of file has been reached, stop adding packets to windows
                            try:
                                print("Attempting to make data packet to fill to-be-sent window")
                                # Computes amount of data that should be read in packet
                                # Space in to-be-sent window exceeds max data length
                                if sr_machine.remaining_space_in_to_be_sent_window() > MAX_DATA_LEN:
                                    data_len = MAX_DATA_LEN
                                # Space in to-be-sent window is <= max data length
                                else:
                                    data_len = sr_machine.remaining_space_in_to_be_sent_window()
                                # Reads data from file
                                data, data_iter = read_out(args.filename, data_start=data_iter, data_len=data_len)

                                # If EOF
                                print("Read data length: ", len(data))
                                if len(data) == 0:
                                    print("Read data with length 0")
                                    break

                                # Makes new packet object with read data
                                data_segment = TCPSegment(data=data, source_port=args.clientport, dest_port=args.serverport,
                                                          seq_num=sequence_num,
                                                          ack_num=acknowledge_num, window=window)
                                # Adds packet to to-be-sent window
                                sr_machine.add_pack_to_to_be_sent_window(data_segment)
                                # Updates seq_num to seq_num + len(data)
                                sequence_num += len(data)

                                # End Of File has been reached, must wait until all data
                                # packets have been sent before going to FIN-Wait-1
                            except EOFError:
                                print("Received EOF Error")
                                break

                            # If to-be-sent window is full
                            if sr_machine.check_if_to_be_sent_window_full():
                                break

                # If sent window is empty, EOF has been reached, send FIN and go to FIN-Wait-1 state
                if sr_machine.check_if_sent_window_empty():  # Checks if sent window has un-acked packets in it still
                    print("Reached EOF, done transmitting data, sending FIN, leaving estab")
                    # Makes new packet object
                    fin_packet = make_packet(pack_type="fin", arguments=args, window=window,
                                             seq_num=sequence_num, ack_num=acknowledge_num)
                    # Increment seq num by 1, similar to sending syn packet
                    sr_machine.seq_num += 1
                    # Sets packet as an FIN packet
                    fin_packet.build_FIN_packet()
                    # Sends packet
                    send(fin_packet, clientSocket)
                    # Transitions into Fin-wait-1 state
                    tcp_machine.close()
                    break

                else:  # Window has un-acked packets
                    # Checks all un-acked packets for timeouts, re-sends if timed-out
                    check_for_timeouts(sr_machine, clientSocket)

            sr_machine.seq_num = sequence_num
            sr_machine.ack_num = acknowledge_num

            # Leaving ESTAB, starting to close

            if tcp_machine.is_fin_wait_1:  # In Fin-wait-1
                # Receive packet and turns incoming bytes message into TCPSegment object
                incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)

                # Loop for receiving valid ack packet
                while True:
                    # Received ack packet
                    if incoming_packet.get_type() == "ack":

                        # Incoming ack has unexpected ack_num
                        if incoming_packet.ack_num != sequence_num:

                            # Gets new received packet, resends syn packet on timeout
                            incoming_packet = rec_resend_pack(fin_packet, clientSocket)

                        # Incoming ack packet has expected ack num
                        else:  # Leaving FinWait-1 through rcv_ack_of_fin()
                            # Increment ack_num by one because of empty ack received
                            acknowledge_num += 1
                            print("Received valid ack of fin, moving to fin-wait-2")
                            # Move to fin-wait-2
                            tcp_machine.rcv_ack_of_fin()
                            break  # Leave loop

                    # Packet is not of expected type
                    else:
                        # Receive packet
                        incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)
                        pass  # Loop through and check new received packet

            # In Fin-wait-2
            if tcp_machine.is_fin_wait_2:
                # Receive packet and turns incoming bytes message into TCPSegment object
                incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)
                # Loop for receiving valid fin packet
                while True:
                    # Received ack packet
                    if True:
                    # if incoming_packet.get_type() == "fin":
                        print("Received fin in fin wait 2, sending ack, moving to time-wait state")
                        # Incoming fin has unexpected seq_num
                        # if incoming_packet.seq_num != acknowledge_num:
                            # Gets new received packet
                            # incoming_packet = rec_pack(clientSocket, depth=MAX_RECV_ATTEMPTS)
                        # Incoming fin packet has expected seq_num
                        # else:  # Leaving Fin-Wait-2 through rcv_fin()
                        # Increment ack_num by one because of fin received
                        acknowledge_num += 1
                        print("Received valid fin, sending ack, moving to Time Wait")
                        # Make ack for fin received
                        ack_packet = make_packet("ack", seq_num=sequence_num, ack_num=acknowledge_num, window=window,
                                                 arguments=args)
                        # Send ack packet
                        send(ack_packet, clientSocket)
                        # Increment seq_num
                        sequence_num += 1
                        # Move to Time Wait
                        tcp_machine.rcv_fin()
                        break  # Leave loop
                    # Packet is not of expected type
                    else:
                        # Receive packet
                        incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)
                        pass  # Loop through and check new received packet

        # If read mode
        else:
            rec_window = list()
            ack_list = list()
            # Variable to store seq_num of next available spot in rec_window
            next_rec_seq_num = acknowledge_num

            # Create empty file with filename to write to
            with open(args.filename, "ba") as file_object:
                file_object.close()

            while True:
                # Receive packet and turns incoming bytes message into TCPSegment object
                incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)

                # Received FIN packet
                if incoming_packet.get_type() == "fin":
                    print("Received fin packet")
                    # If receive window is not empty, wait for missing data packets
                    if len(rec_window) > 0:
                        print("Receive window is not empty, waiting for missing data")
                        # Get next packet
                        incoming_packet = rec_pack(clientSocket, depth=MAX_RECV_ATTEMPTS)
                        pass  # Loop through and check new received packet
                    # If receive window is empty, aka, all data has been received
                    else:
                        # Check that fin packet has correct seq_num
                        if incoming_packet.seq_num == acknowledge_num:
                            # Increment ack_num due to size of fin packet
                            acknowledge_num += 1
                            # Create ack of received fin
                            ack_packet = make_packet("ack", seq_num=sequence_num, ack_num=acknowledge_num,
                                                     arguments=args,
                                                     window=window)
                            # Send ack
                            send(ack_packet, clientSocket)
                            # Increment seq_num
                            sequence_num += 1
                            # Go to close-wait state
                            tcp_machine.rcv_fin()
                            break
                        else:
                            print("Received fin with incorrect seq_num in Estab, expecting: ", acknowledge_num,
                                  "received: ", incoming_packet.seq_num)
                            pass

                # Received data packet
                elif (incoming_packet.get_type() == "data") | \
                        ( (incoming_packet.get_type() == "ack") & (len(incoming_packet.data) > 0) ):
                    repeat_pack = False
                    # Search ack_list for ack of incoming packet, resend ack if found
                    for x in ack_list:
                        if x.ack_num == incoming_packet.seq_num + len(incoming_packet.data):
                            send(x, clientSocket)
                            # Showing that incoming packet has been recognized as repeat packet
                            repeat_pack = True

                    # Incoming seq_num is >= next expected byte of data and isn't a repeat
                    if incoming_packet.seq_num >= next_rec_seq_num & (not repeat_pack):
                        # Add packet to rec_wnd
                        add_pack_to_rec_window(incoming_packet, rec_window)
                        # Increment acknowledge_num equal to length of incoming_packet data
                        acknowledge_num += len(incoming_packet.data)
                        # Make ack for received packet
                        ack_packet = make_packet("ack", seq_num=sequence_num, ack_num=acknowledge_num, arguments=args,
                                                 window=window)
                        # Increment seq_num by 1 for sending empty ack
                        sequence_num += 1
                        # Send ack packet
                        send(ack_packet, clientSocket)
                        # If ack_list is getting long
                        if len(ack_list) > 100:
                            # Remove oldest ack
                            ack_list.pop(0)
                            # Add new ack to end of list
                            ack_list.append(ack_packet)
                        else:
                            # Add ack_packet to ack_list
                            ack_list.append(ack_packet)
                        # Write data and remove packets from rec_window if rec_window has correct packet order
                        while rec_window[0].seq_num == next_rec_seq_num:
                            # Read in data from packet
                            read_in(rec_window[0].data, args.filename)
                            # Increment seq_num of next packet to be written
                            next_rec_seq_num += len(rec_window[0].data)
                            # Remove written packet from rec_window
                            rec_window.pop(0)
                            # Check if rec_window is empty
                            if len(rec_window) == 0:
                                break

                # Received packet of unexpected type
                else:
                    # Gets new received packet
                    incoming_packet = rec_pack(clientSocket, depth=MAX_RECV_ATTEMPTS)
                    print("Received packet of unexpected type")
                    pass  # Loop through and check new received packet

            # In close-wait state

            if tcp_machine.is_close_wait:
                # Create fin packet
                fin_packet = make_packet("fin", seq_num=sequence_num, ack_num=acknowledge_num, arguments=args,
                                         window=window)
                # Send fin packet
                send(fin_packet, clientSocket)
                # Increment seq_num
                sequence_num += 1
                # Go to last-ack state
                tcp_machine.close()
            else:
                print("Broke state machine, supposed to be in Close-wait state")
                exit()

            # In last-ack state

            if tcp_machine.is_last_ack:
                # Receive valid ack of fin
                while True:
                    # Receive packet
                    incoming_packet = rec_pack(sckt=clientSocket, depth=MAX_RECV_ATTEMPTS)
                    # Correct packet type
                    if incoming_packet.get_type() == "ack":
                        print("Received correct ack of fin in last-ack state, "
                              "doing nothing and closing connection, well done")
                        break
            else:
                print("Broke state machine, supposed to be in Last-ack state")
                exit()

    terminate_connection()

    # Connection is through, we are done =<]
