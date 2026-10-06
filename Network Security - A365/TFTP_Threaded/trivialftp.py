from socket import *
from deconstructpacket import *
from constructpacket import *
from readinfile import *
from readoutfile import *


def read_mode(clientAddress, serverport, filename):
    # Create new socket for thread
    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    clientSocket.bind(("127.0.0.1", serverport))
    clientSocket.connect(clientAddress)

    prev_block = 0
    packet = build_ack(0, 0)

    while True:
        i = 0
        while True:
            try:
                clientSocket.settimeout(5)
                clientSocket.sendto(packet, clientAddress)
                packet_tuple = clientSocket.recvfrom(2048)
                data = packet_tuple[0]
                break
            except:
                if i > 50:
                    exit()
                i += 1
                print("Trying to send/receive packets")

        if data[1] == 3:
            block = data[2]*256 + data[3]
            opcode = data[0] + data[1]
            if block == prev_block + 1:
                d_tuple = unpack_DATA(filename, data)
                if len(data) < 516:
                    packet = build_ack(data[2], data[3])
                    clientSocket.sendto(packet, clientAddress)
                    break

                else:
                    packet = build_ack(data[2], data[3])
                prev_block += 1

                if block == 65535:
                    print("Activated")
                    prev_block = -1

            else:
                print("Packet received out of order")
                packet = build_error(4, "Illegal TFTP Operation")
                clientSocket.sendto(packet, clientAddress)
                break

        if opcode == 5:
            print("Received an error packet")
            break

    clientSocket.close()
    exit()


def write_mode(clientAddress, serverport, filename):
    # Create new socket for thread
    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    clientSocket.bind(("127.0.0.1", serverport))
    clientSocket.connect(clientAddress)

    data_file = read_out(filename)

    ack = ""
    index = 0

    packet = build_data(int.to_bytes(1, 2, "big"), data_file[index])
    index += 1

    while True:
        i = 0
        while True:
            try:
                clientSocket.settimeout(5)
                clientSocket.sendto(packet, clientAddress)
                packet_tuple = clientSocket.recvfrom(2048)
                ack = packet_tuple[0]
                break
            except:
                if i > 50:
                    exit()
                i += 1
                print("Trying to send/receive packet")

        if len(data_file) == 0:
            break

        if len(data_file[index]) < 512:
            block = unpack_ACK(ack)
            block = int.from_bytes(block, "big")
            block += 1
            block = int.to_bytes(block, 2, "big")
            packet = build_data(block, data_file[index])
            index += 1
            clientSocket.sendto(packet, clientAddress)
            break

        else:
            block = unpack_ACK(ack)
            block = int.from_bytes(block, "big")
            block += 1
            block = int.to_bytes(block, 2, "big")
            packet = build_data(block, data_file[index])
            index += 1
    clientSocket.close()
    exit()
