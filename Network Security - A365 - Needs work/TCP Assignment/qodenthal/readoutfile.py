def read_out(filename, data_start, data_len):
    print("Attempting to read ", data_len, " bytes of data starting at ", data_start)
    with open(filename, "br") as f:
        f.seek(data_start, 0)  # Uses data iterator to determine where to start reading file
        data = f.read(data_len)
        if len(data) != data_len:    # End of file / last data transmission
            print("Read last segment of data, next packet should be fin")
            f.close()
        else:
            f.close()
    print("Read ", len(data), " bytes of data out of ", data_len)
    return data, data_start + len(data)  # Returns data and index of next new piece of data
