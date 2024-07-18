#########################################
# Quinton Odenthal
# Assignment 2
# 10/21/20
#
# Description: This program plays the song "A Cruel Angel's Thesis by Yoko Takahashi".
# Inputs: A three length tuple including the note's pitch, duration, and velocity respectively.
# Outputs: Plays a song.
#########################################

# https://www.pygame.org/docs/ref/midi.html
import pygame
import pygame.midi
import time


## initialize midi player
pygame.midi.init()
player = pygame.midi.Output(0)
# for the list of MIDI instruments:
#    https://soundprogramming.net/file-formats/general-midi-instrument-list/
player.set_instrument(0)

## play notes
def play_note_wait(tone, duration, velocity):
    '''
        Description: This function plays a note.
        Inputs: tone -- determines tone of note, duration -- determines length of note, and velocity -- determines volume of note.
        Returned value: n/a.
        Preconditions: note and velocity must be 0 - 127 and duration must be >= 0.
    '''
    player.note_on(tone, velocity)
    time.sleep(duration)
    player.note_off(tone, velocity)

note_list = [
    (60,0.8,127)
    ,(63,0.8,127)
    ,(65,0.6,127)
    ,(64,0.6,127)
    ,(65,0.4,127)
    ,(65,0.4,127)
    ,(65,0.4,127)
    ,(70,0.4,127)
    ,(69,0.4,127)
    ,(68,0.2,127)
    ,(67,0.4,127)
    ,(68,0.5,127)
    ,(65,0.4,0)
    ,(68,0.8,127)
    ,(70,0.8,127)
    ,(71,0.6,127)
    ,(67,0.6,127)
    ,(66,0.4,127)
    ,(70,0.4,127)
    ,(70,0.4,127)
    ,(68,0.4,127)
    ,(70,0.4,127)
    ,(70,0.6,127)
    ,(71,1.0,127)
    ]

for note in note_list:
    play_note_wait(*note)

## clean up player and pygame objects
del player
pygame.midi.quit()
