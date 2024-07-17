from bitstring import Bits, BitArray
from time import perf_counter


class TCPSegment:
    SEGMENT_LEN = 1500 - 20 - 8  # Number of bytes in header and data
    HEADER_WORDS = 5    # Number of 32-bit words in header
    HEADER_LEN = HEADER_WORDS * 4
    DATA_LEN = SEGMENT_LEN - HEADER_LEN  # 1452-byte max

    # My additions

    status = "not sent"  # Status of packet
    max_timer = 0.5  # Time in second before timeout occurs
    send_counter = 0  # Number of times packet has been sent
    send_max = 50  # Number of available sends before error is thrown
    clock = 0  # Global time of system
    start_time = 0  # Global time of when packet was sent, marks start of timer

    def __init__(self, data, source_port, dest_port, seq_num=0, ack_num=0,
                 window=1500, is_ack=False, is_syn=False, is_fin=False):
        if len(data) > self.DATA_LEN:
            raise ValueError("Data length of " + str(len(data)) + " exceeds max of " + str(self.DATA_LEN))
        if source_port >= 2 ** 16:
            raise ValueError("Source port too high")
        if window >= 2 ** 16:
            raise ValueError("Window too large")
        if source_port < 0 or dest_port < 0 or seq_num < 0 or ack_num < 0 or window < 0:
            raise ValueError("Negative values not allowed")
        self.data = data
        self.source_port, self.dest_port = source_port, dest_port
        self.seq_num, self.ack_num = seq_num % (2 ** 32), ack_num % (2 ** 32)
        self.window = window
        self.is_ack, self.is_syn, self.is_fin = is_ack, is_syn, is_fin

        # My additions

        self.exp_ack_num = self.seq_num + len(self.data)  # Value of expected ack

    """Returns bytes equivalent"""

    def to_bytes(self):
        num = 0
        array = BitArray(self.source_port.to_bytes(2, "big") + self.dest_port.to_bytes(2, "big")
                         + self.seq_num.to_bytes(4, "big") + self.ack_num.to_bytes(4, "big")
                         + b"\0\0" + self.window.to_bytes(2, "big") + b"\0\0\0\0" + self.data)  # Assemble segment
        array[96:100] = Bits(self.HEADER_WORDS.to_bytes(1, "big"))[4:8]  # Set data offset bits
        array[107], array[110], array[111] = self.is_ack, self.is_syn, self.is_fin  # Set control bits
        array[128:144] = Bits(num.to_bytes(2, "big"))  # Set checksum to all 0's
        return array.tobytes()

    '''Helper methods for building packets'''

    def set_window(self, window):
        self.window = window
        self.to_bytes()

    def set_data(self, data):
        self.data = data
        self.to_bytes()

    def build_packet(self, data=None, dest_port=None, seq_num=None, ack_num=None):
        self.is_syn = False
        self.is_fin = False
        self.is_ack = False
        if data is None:
            self.data = self.data
        else:
            self.data = data

        if dest_port is None:
            self.dest_port = self.dest_port
        else:
            self.dest_port = dest_port

        if seq_num is None:
            self.seq_num = self.seq_num
        else:
            self.seq_num = seq_num

        if ack_num is None:
            self.ack_num = self.ack_num
        else:
            self.ack_num = ack_num

        return self.to_bytes()

    def build_SYN_packet(self, seq_num=None):
        self.is_fin = False
        self.is_ack = False
        self.is_syn = True
        if seq_num is None:
            self.seq_num = self.seq_num
        else:
            self.seq_num = seq_num

        self.exp_ack_num = self.seq_num + 1

        return self.to_bytes()

    def build_SYNACK_packet(self, data=None, seq_num=None, ack_num=None, dest_port=None):
        self.is_syn = True
        self.is_fin = False
        self.is_ack = True

        if seq_num is None:
            self.seq_num = self.seq_num
        else:
            self.seq_num = seq_num

        if ack_num is None:
            self.ack_num = self.ack_num
        else:
            self.ack_num = ack_num

        if data is None:
            self.data = self.data
        else:
            self.data = data

        if dest_port is None:
            self.dest_port = self.dest_port
        else:
            self.dest_port = dest_port

        self.exp_ack_num = self.seq_num + 1

        return self.to_bytes()

    def build_ACK_packet(self, data=None, seq_num=None, ack_num=None, dest_port=None):
        self.is_syn = False
        self.is_fin = False
        self.is_ack = True

        if data is None:
            self.data = self.data
        else:
            self.data = data

        if dest_port is None:
            self.dest_port = self.dest_port
        else:
            self.dest_port = dest_port

        if seq_num is None:
            self.seq_num = self.seq_num
        else:
            self.seq_num = seq_num

        if ack_num is None:
            self.ack_num = self.ack_num
        else:
            self.ack_num = ack_num

        return self.to_bytes()

    def build_FIN_packet(self, seq_num=None, ack_num=None):
        self.is_fin = True
        self.is_syn = False
        self.is_ack = True

        if seq_num is None:
            self.seq_num = self.seq_num
        else:
            self.seq_num = seq_num

        if ack_num is None:
            self.ack_num = self.ack_num
        else:
            self.ack_num = ack_num

        self.exp_ack_num = self.seq_num + 1

        return self.to_bytes()

    # My additions

    def get_timer(self):
        return perf_counter() - self.clock  # Returns time since timer started

    def reset_timer(self):
        self.clock = perf_counter() # Restarts the timer

    def send(self):
        if self.status == "acked":
            self.reset_timer()
        else:
            self.status = "sent"
            self.reset_timer()

    def acknowledge(self):
        self.status = "acked"

    def data_len(self):
        return len(self.data)

    def get_type(self):
        if self.is_syn == 1 & self.is_ack == 1:
            return "syn,ack"
        elif self.is_fin == 1 & self.is_ack == 1:
            return "fin"
        elif self.is_syn == 1:
            return "syn"
        elif self.is_ack == 1:
            return "ack"
        else:
            return "data"
