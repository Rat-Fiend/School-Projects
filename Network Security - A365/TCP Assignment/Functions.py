import random
from TCPSegment import *
from SelectiveRepeat import *
from bitstring import Bits, BitArray
from readoutfile import *
from socket import *


def make_packet(pack_type, seq_num, ack_num, arguments, window):
    tmp_seg = TCPSegment(data=bytes(), source_port=arguments.clientport, dest_port=arguments.serverport,
                         seq_num=seq_num, ack_num=ack_num, window=window)
    # print("Segment created with sourceport: ", arguments.clientport, " and destport: ", arguments.serverport)
    if pack_type == "ack":
        tmp_seg.build_ACK_packet(data=bytes(), seq_num=seq_num,
                                 ack_num=ack_num, dest_port=arguments.serverport)
        return tmp_seg

    elif pack_type == "fin":
        tmp_seg.build_FIN_packet(seq_num=seq_num, ack_num=ack_num)
        return tmp_seg

    elif pack_type == "syn":
        tmp_seg.build_SYN_packet(seq_num=seq_num)
        return tmp_seg

    else:  # Packet type is syn,ack
        tmp_seg.build_SYNACK_packet(data=bytes(), seq_num=seq_num,
                                    ack_num=ack_num, dest_port=arguments.serverport)
        return tmp_seg


# Recursion mode, attempts to receive packet depth number of times before throwing error
def rec_pack(sckt, depth):
    try:
        # Receive new packet
        incoming_packet = sckt.recv(1500)
        # Turns incoming bytes message into TCPSegment object
        return bytes_to_tcpsegment(incoming_packet)  # This is how we leave the recursion
    except ValueError:
        print(ValueError)
    except:
        if depth < 1:
            raise ValueError("Max number of recv() attempts reached, closing connection")
        print("socket.recv() timed out, ", depth, " attempts remaining")
        return rec_pack(sckt, depth - 1)


# # Infinite loop mode, runs until a packet is received
# def rec_pack(sckt):
#     # Gets new received packet
#     while True:
#         try:
#             # Receive new packet
#             incoming_packet = sckt.recv(1500)
#             # Turns incoming bytes message into TCPSegment object
#             return bytes_to_tcpsegment(incoming_packet)
#         except:
#             print("socket.recv() timed out")
#             pass


# Infinite loop mode, runs until a packet is received, resends packet if timeout
def rec_resend_pack(packet, sckt):
    # Gets new received packet
    while True:
        try:
            # Receive new packet
            incoming_packet = sckt.recv(1500)
            # Turns incoming bytes message into TCPSegment object
            return bytes_to_tcpsegment(incoming_packet)
        except socket.timeout:
            print("socket.recv() timed out")
            send(packet, sckt)  # Resend syn packet
            pass


def get_random_seq_num():
    random_number = random.randint(0, 2 ** 32)
    return random_number


def create_tcb():
    print("TCB object created")
    return "TCB object"


def delete_tcb():
    print("TCB deleted")
    return "TCB deleted"


def close_command():
    """Closes stuff"""


def bytes_to_tcpsegment(msg):
    msg = BitArray(msg)
    # Creates segment using msg received
    headerwords = msg[96:100].uint
    sourceport = msg[0:16].uint
    destport = msg[16:32].uint
    seqnum = msg[32:64].uint
    acknum = msg[64:96].uint
    window = msg[112:128].uint
    # print("Converted packet info:")
    # print("\nHead words: ", headerwords)
    # print("Source port: ", sourceport)
    # print("Destination port: ", destport)
    # print("Sequence number: ", seqnum)
    # print("Acknowledgment number: ", acknum)
    # print("Window: ", window)
    data = msg[(headerwords * 32):].bytes  # Data location calculated dynamically using header words info
    isack = msg[107]
    issyn = msg[110]
    isfin = msg[111]
    # print("Data length: ", len(data))
    # print("Ack flag: ", isack)
    # print("Syn flag: ", issyn)
    # print("Fin flag: ", isfin)

    tmp = TCPSegment(source_port=sourceport, dest_port=destport,
                     seq_num=seqnum, ack_num=acknum,
                     window=window, data=data, is_ack=isack, is_syn=issyn, is_fin=isfin)
    return tmp  # Returns received bytes packet as a TCPSegment object, segment type


# Checks ack_num of packet vs exp_ack_num
def check_ack_num_vs_exp_ack(segment, exp_ack_num):
    if segment.ack_num == exp_ack_num:
        print("Received message with expected ack_num")
        return True
    else:
        print("Received message with un-expected ack_num")
        return False


# Checks ack_num is in range for sent window
def check_ack_num_in_range(selectiverepeat, ack_num):
    # If ack is in acceptable range, return True
    print("Checking ack is in range: ", selectiverepeat.to_be_sent_window[0].seq_num, " >= ",
          ack_num, " > ", selectiverepeat.oldest_unacked_seq_num())
    # Ack must be greater than seq_num of oldest unacked packet,
    # and less than or equal to seq_num of next packet to be sent - RFC 793
    if (ack_num > selectiverepeat.oldest_unacked_seq_num()) & (ack_num <= selectiverepeat.to_be_sent_window[0].seq_num):
        print("Ack_num in range")
        return True
    else:
        print("Ack_num not in range")
        return False


def terminate_connection():
    return "Connection terminated"


# Definitions for selective repeat stuff


# Returns True if received ack_num corresponds to packet in sent list
def check_valid_ack(selectiverepeat, ack_num):
    for x in selectiverepeat.sent_window:
        if ack_num == x.exp_ack_num:  # Ack applies to current packet
            return True
    return False


def ack_pack_in_list(selectiverepeat, ack_num):  # Iterates through send list and acks packet with seq+len == ack num
    print("Checking sent list for unacked packets, acking packet with expected ack_num: ", ack_num)
    i = 0
    for x in selectiverepeat.sent_window:
        print("Packet number ", i, ": ", x.status, ", and ", x.exp_ack_num)
        if ack_num == x.exp_ack_num:  # Ack applies to current packet
            print()
            if x.status == "acked":  # Current packet is already acked
                return False  # Nothing changed, returns False
            else:
                print("Packet number: ", i, " has been acknowledged")
                x.acknowledge()  # Sets packet state to acknowledged
                return True  # Packet state has changed
        else:
            pass
        i += 1
    return False


def add_pack_to_windows(selectiverepeat, packet, sckt):
    if selectiverepeat.check_if_to_be_sent_window_empty():  # If to-be-sent window is empty
        if selectiverepeat.check_if_pack_can_fit_sent_window():  # If segment can fit in sent window
            send(packet, sckt)  # Send packet
            packet.send()  # Set status to sent, starts timer
            selectiverepeat.add_pack_to_sent_window(packet)  # Add packet directly to sent window
        else:  # Segment can't fit in sent window
            selectiverepeat.add_pack_to_to_be_sent_window(packet)  # Add segment to to-be-sent window
    else:  # To-be-sent window is not empty
        selectiverepeat.add_pack_to_to_be_sent_window(packet)  # Add segment to to-be-sent window


# Tries to shift and send to-be-sent packets into sent window while to-be-sent window is not empty
def shift_to_be_sent_into_sent(selectiverepeat, sckt):
    print("Attempting to shift packets from to-be-sent into sent and send them")
    while not selectiverepeat.check_if_to_be_sent_window_empty():  # While to-be-sent window is not empty
        print("To-be-sent window is not empty")
        # If first packet of to-be-sent window can't fit into sent window
        if not selectiverepeat.check_if_packet_can_fit_sent_window(selectiverepeat.to_be_sent_window[0]):
            print("First packet of to-be-sent window cannot fit into sent window, done shifting")
            break
        else:  # First packet of to-be-sent window can fit into sent
            print("First packet of to-be-sent window can fit into sent window, sending it, moving it to sent window")
            send(selectiverepeat.to_be_sent_window[0], sckt)  # Sends packet and updates packet status and timer
            # Add to-be-sent packet to sent window, and remove from to-be-sent window
            selectiverepeat.sent_window.append(selectiverepeat.to_be_sent_window.pop(0))


def check_for_timeouts(selectiverepeat, sckt):
    print("Checking for timeouts")
    for x in range(len(selectiverepeat.sent_window)):
        if selectiverepeat.sent_window[x].status == "acked":  # If package is already acked, ignore it
            pass
        else:
            check_time(selectiverepeat.sent_window[x], sckt)  # Checks if packet has timed out, re-sends if timed-out


# Definitions for Packet obj


def check_time(packet_obj, sckt):  # Checks for timeout
    print("Checking timer for ", packet_obj.seq_num, " packet. Timer: ", packet_obj.get_timer())
    if packet_obj.get_timer() < packet_obj.max_timer:  # No timeout
        pass
    else:  # Timeout has occurred, packet must be re-sent
        if packet_obj.send_counter >= packet_obj.send_max:  # Max number of available packet sends reached
            raise ValueError("Packet sent too many times, connection lost")
        else:
            print("Resending packet")
            send(packet_obj, sckt)


def send(packet, sckt):
    sckt.send(packet.to_bytes())
    packet.send()

def add_pack_to_rec_window(packet, rec_wnd):
    # This method uses the assumption that any packet given to it will not be a repeat packet
    for x in range(len(rec_wnd)):
        # If packet to be added has a lesser seq_num than a packet in rec_wnd
        if packet.seq_num < rec_wnd[x].seq_num:
            # Add before target packet
            rec_wnd.insert(x, packet)
            return
    # New packet has greater seq_num than all packets in rec_wnd, add to end of list
    rec_wnd.append(packet)
