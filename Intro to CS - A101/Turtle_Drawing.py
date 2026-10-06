#########################################
# Quinton Odenthal
# Assignment 1
# 9 / 27 / 2020
#
# Description: This program prints a turtle on a canvas.
# Inputs: N/A
# Outputs: Picture of turtle.
#########################################

#Canvas dimensions
from tkinter import *

canvas_width = 800
canvas_height = 600

colours = ("#476042", "yellow")
oval=[]

#Shell dimensions
for ratio in ( 0.2, 0.35 ):
   oval.append( (canvas_width * ratio,
                canvas_height * ratio,
                canvas_width * (1 - ratio),
                canvas_height * (1 - ratio) ) )

#Leg allignments
legs=[]

for ratio in ( 0.3, 0.4 ):
   legs.append( (canvas_width * ratio,
                canvas_height * ratio,
                canvas_width * (1 - ratio),
                canvas_height * (1 - ratio) ) )

master = Tk()

w = Canvas(master,
           width=canvas_width,
           height=canvas_height)
w.pack()

#Making the background
w.create_rectangle(0, 0, canvas_width, canvas_height, fill="#0000ff")

#Making the tail
tail_points = (oval[0][0] + 1, (canvas_height / 2) - 10,
              oval[0][0] - 20, canvas_height / 2,
              oval[0][0] + 1, (canvas_height / 2) + 10)

w.create_polygon(tail_points, width=3)

#Making the legs
nw_leg_points = (legs[0][0] - 20, legs[0][1] + 20,
                legs[0][0] - 100, legs[0][1] - 30,
                legs[0][0] + 10, legs[0][1] - 10)

ne_leg_points = (legs[0][2] + 20, legs[0][1] + 20,
                legs[0][2] + 100, legs[0][1] - 30,
                legs[0][2] - 10, legs[0][1] - 10)

sw_leg_points = (legs[0][0] - 20, legs[0][3] - 20,
                legs[0][0] - 100, legs[0][3] + 30,
                legs[0][0] + 10, legs[0][3] + 10)

se_leg_points = (legs[0][2] + 20, legs[0][3] - 20,
                legs[0][2] + 100, legs[0][3] + 30,
                legs[0][2] - 10, legs[0][3] + 10)

w.create_polygon(nw_leg_points, width=3)

w.create_polygon(ne_leg_points, width=3)

w.create_polygon(sw_leg_points, width=3)

w.create_polygon(se_leg_points, width=3)

#Making the head
w.create_oval(oval[0][2] - 20, (canvas_height / 2) - 40, oval[0][2] + 100, (canvas_height / 2) + 40, fill=colours[0])

w.create_oval((oval[0][2] + 80) - 3, ((canvas_height / 2) - 10) - 3, (oval[0][2] + 80) + 3, ((canvas_height / 2) - 10) + 3)

w.create_oval((oval[0][2] + 80) - 3, ((canvas_height / 2) + 10) - 3, (oval[0][2] + 80) + 3, ((canvas_height / 2) + 10) + 3)

#Making the shell
w.create_oval(oval[0][0],oval[0][1],oval[0][2],oval[0][3], fill=colours[0])

#Making the text
w.create_text(canvas_width / 2,
              canvas_height / 2,
              text="Turtle")
mainloop()