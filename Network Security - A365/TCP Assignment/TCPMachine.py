from statemachine import State, StateMachine


class TCPMachine(StateMachine):

    # States

    closed = State("Closed", initial=True)
    listen = State("Listen")
    syn_sent = State("Syn-sent")
    syn_rcvd = State("Syn-received")
    estab = State("ESTAB")
    fin_wait_1 = State("FIN-wait-1")
    fin_wait_2 = State("FIN-wait-2")
    close_wait = State("Close-wait")
    closing = State("Closing")
    last_ack = State("Last-ACK")
    time_wait = State("Time-wait")

    # 3-way handshake transitions

    active_open = closed.to(syn_sent)
    passive_open = closed.to(listen)
    rcv_syn = syn_sent.to(syn_rcvd) | listen.to(syn_rcvd)
    send = listen.to(syn_sent)
    rcv_synack = syn_sent.to(estab)
    rcv_ack_of_syn = syn_rcvd.to(estab)

    # Closing transitions

    rcv_fin = estab.to(close_wait) | fin_wait_1.to(closing) | fin_wait_2.to(time_wait)
    close = estab.to(fin_wait_1) | close_wait.to(last_ack) | syn_sent.to(closed) | \
            listen.to(closed) | syn_rcvd.to(fin_wait_1)
    rcv_ack_of_fin = last_ack.to(closed) | fin_wait_1.to(fin_wait_2) | closing.to(time_wait)
    timeout_2msl = time_wait.to(closed)

    # # Actions on 3-way handshake transitions
    #
    # def on_active_open(self):
    #     create_tcb()
    #     snd_syn()
    #
    # def on_passive_open(self):
    #     create_tcb()
    #
    # def on_rec_syn(self):
    #     if self.is_listen:  # If leaving listen state
    #         snd_synack()
    #     else:   # If leaving syn_sent state
    #         snd_ack()
    #
    # def on_send(self):
    #     snd_syn()
    #
    # def on_rcv_synack(self):
    #     snd_ack()
    #
    # def on_rec_ack_of_syn(self):
    #     return
    #
    # # Actions on closing transitions
    #
    # def on_rcv_fin(self):
    #     snd_ack()
    #
    # def on_close(self):
    #     if self.is_listen | self.is_syn_sent:
    #         delete_tcb()
    #     else:
    #         snd_fin()
    #
    # def on_rec_ack_of_fin(self):
    #     return
    #
    # def on_timeout_2msl(self):
    #     delete_tcb()