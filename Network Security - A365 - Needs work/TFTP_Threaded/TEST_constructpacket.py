import pytest
from constructpacket import *


def test_build_ack():
    assert build_ack(0, 5) == b'\x00\x04\x00\x05'


def test_build_data():
    assert build_data(int.to_bytes(100, 2, "big"), "This is my test data") == b'\x00\x03' + int.to_bytes(100, 2, "big") \
           + b'This is my test data'

def test_build_wrq():
    assert build_wrq("test_filename.test", )

# def test_build_rrq()
# def test_build_error()
# def test_build_request_packet()