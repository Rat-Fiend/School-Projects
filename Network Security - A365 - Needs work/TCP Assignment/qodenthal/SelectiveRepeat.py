from TCPSegment import *
from readoutfile import read_out
from readinfile import read_in


class SelectiveRepeat:
    sent_window = list()
    to_be_sent_window = list()
    rec_window = list()
    acked_list = list()
    written_list = list()
    data_iter = 0  # Marks next new byte of data to be sent
    end = False  # Marks if end of file has been reached, used to leave loop

    def __init__(self, filename, address, source_port, dest_port, wnd_size, rec_wnd_size, seq_num, ack_num,
                 state_machine):
        self.filename = filename
        self.address = address
        self.source_port, self.dest_port = source_port, dest_port
        self.window_size = wnd_size
        self.rec_window_size = rec_wnd_size
        self.rec_data_iter = ack_num
        self.seq_num, self.ack_num = seq_num, ack_num
        self.state_machine = state_machine

    # def new_data_packet(self):
    #     if self.end:  # End of file reached, return nothing
    #         return
    #     data = read_out(data_start=self.data_iter, filename=self.filename, data_len=)  # Gets data from file
    #     self.data_iter += len(data)  # Moves data iterator equal to length of data gathered
    #     if len(data) < 1452:  # End of file reached
    #         self.end = True
    #     temp = Packet(data=data, source_port=self.source_port, dest_port=self.dest_port,
    #                   seq_num=self.seq_num, ack_num=self.ack_num, address=self.address)
    #     self.seq_num = (self.seq_num + len(data)) % (2 ** 32)  # Increments seq_num equal to length of data read
    #     return temp  # Return newly created data packet with fresh data

    def check_if_sent_window_empty(self):
        if len(self.sent_window) == 0:  # If sent window is empty, return true, otherwise, false
            return True
        else:
            return False

    def check_if_to_be_sent_window_empty(self):
        if len(self.to_be_sent_window) == 0:  # If to-be-sent window is empty, return true, otherwise, false
            return True
        else:
            return False

    def check_if_rec_window_empty(self):
        if len(self.rec_window) == 0:  # If received window is empty, return true, otherwise, false
            return True
        else:
            return False

    def check_if_sent_window_full(self):
        if self.data_in_sent_window() < self.window_size:
            return False  # If window is not full of data, return False
        else:
            return True  # If window is full of data return True

    def check_if_to_be_sent_window_full(self):
        if self.data_in_to_be_sent_window() < self.window_size:
            return False  # If window is not full of data, return False
        else:
            return True  # If window is full of data return True

    def check_if_packet_can_fit_sent_window(self, packet):
        # If length of packet data and sent window data combined exceeds window size
        if (packet.data_len() + self.data_in_sent_window()) > self.window_size:
            return False
        else:  # Packet can fit in sent window
            return True

    def check_if_packet_can_fit_to_be_sent_window(self, packet):
        # If length of packet data and to-be-sent window data combined exceeds window size
        if (packet.data_len() + self.data_in_to_be_sent_window()) > self.window_size:
            return False
        else:  # Packet can fit in to-be-sent window
            return True

    def data_in_sent_window(self):
        data_total = 0
        for x in self.sent_window:  # Iterates through all packets in sent window
            data_total += x.data_len()  # Adds length of data in packet to data total for window
        return data_total  # Returns total of all data in all packets in sent window

    def data_in_to_be_sent_window(self):
        data_total = 0
        for x in self.to_be_sent_window:  # Iterates through all packets in to-be-sent window
            data_total += x.data_len()  # Adds length of data in packet to data total for window
        return data_total  # Returns total of all data in all packets in to-be-sent window

    # Returns amount of empty data space in sent window
    def remaining_space_in_sent_window(self):
        return self.window_size - self.data_in_sent_window()

    # Returns amount of empty data space in sent window
    def remaining_space_in_to_be_sent_window(self):
        return self.window_size - self.data_in_to_be_sent_window()

    # Returns first (oldest) un-acked packet's seq_num
    def oldest_unacked_seq_num(self):
        if self.sent_window[0].status == "acked":  # Fist packet in sent window shouldn't ever be acked
            raise ValueError("First packet in sent window is acked, did not shift it out")
        else:
            return self.sent_window[0].seq_num

    def shift_out_acked_packets(self):
        print("Trying to shift out acked packets in sent window")
        print("Current window")
        for x in self.sent_window:
            print(x.status, " ", x.seq_num)
        # If sent window is empty, shifting is not necessary, don't do anything
        if self.check_if_sent_window_empty():
            print("Sent window is empty, no shifting necessary")
            return
        while self.sent_window[0].status == "acked":  # While first packet in window is acked
            print("Packet in position 0 is acked, shift it out and check next packet")
            # Add acked packet to acked packet list, and remove from sent window
            self.acked_list.append(self.sent_window.pop(0))
            if len(self.sent_window) == 0:
                break
        print("Window after shift")
        for x in self.sent_window:
            print(x.status, " ", x.seq_num)

    def write_data_packets_to_file(self):
        # If received window is empty, shifting is not necessary, don't do anything
        if self.check_if_rec_window_empty():
            return
        # While first packet in window is next data segment to be written
        while self.rec_window[0].seq_num == self.rec_data_iter:
            read_in(self.rec_window[0].data, self.filename)
            # Increment received data iterator by length of data written
            self.rec_data_iter += len(self.rec_window[0].data)
            # Remove written data packet from received window, add it to written window
            self.written_list.append(self.rec_window.pop(0))

    def add_pack_to_sent_window(self, segment):
        self.sent_window.append(segment)

    def add_pack_to_to_be_sent_window(self, segment):
        self.to_be_sent_window.append(segment)

    def add_pack_to_rec_window(self, segment):
        self.rec_window.append(segment)
