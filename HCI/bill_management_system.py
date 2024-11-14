from tkinter import *  # Import all classes and functions from tkinter library to create GUI

# Create main window
root = Tk() 
root.geometry("1000x500")  # Set window size to 1000x500 pixels
root.title("Bill Management")  # Set window title
root.resizable(False, False)  # Prevent window from being resized

# Function to reset all input fields
def Reset():
    entry_dosa.delete(0, END)  # Clear dosa entry field
    entry_tea.delete(0, END)   # Clear tea entry field
    entry_juice.delete(0, END)  # Clear juice entry field
    entry_eggs.delete(0, END)  # Clear eggs entry field

# Function to calculate the total bill
def Total():
    # Try to get each entry's value; if blank, set it to 0
    try: a1 = int(dosa.get())
    except: a1 = 0
   
    try: a2 = int(tea.get())
    except: a2 = 0

    try: a3 = int(juice.get())
    except: a3 = 0

    try: a4 = int(eggs.get())
    except: a4 = 0

    # Define cost per quantity for each item
    c1 = 60 * a1  # Dosa cost (Rs. 60 per plate)
    c2 = 10 * a2  # Tea cost (Rs. 10 per cup)
    c3 = 30 * a3  # Juice cost (Rs. 30 per glass)
    c4 = 15 * a4  # Eggs cost (Rs. 15 per egg)

    # Display "Total" label in the bill frame (f3)
    lbl_total = Label(f3, font=("aria", 20, "bold"), text="Total", width=18, fg="lightyellow", bg="black")
    lbl_total.place(x=0, y=84)

    # Calculate total cost and display it
    totalcost = c1 + c2 + c3 + c4 
    string_bill = "Rs." + str(totalcost)  # Format total cost as string
    Total_bill.set(string_bill)  # Set total bill amount in Total_bill variable

    # Display the total bill amount in an entry widget
    entry_total = Entry(f3, font=("aria", 20, "bold"), textvariable=Total_bill, bd=6, width=12, bg="lightgreen")
    entry_total.place(x=60, y=140)

# Main title for the application
Label(text="BILL MANAGEMENT", bg="black", fg="white", font=("calibri", 33), width=50, height=2).pack()

# Frame for the menu card
f1 = Frame(root, bg="lightgreen", highlightbackground="black", highlightthickness=1, width=300, height=370)
f1.place(x=10, y=122)  # Place menu frame at specific coordinates

Label(f1, text="Menu", font=("Gabriola", 40, "bold"), fg="black", bg="lightgreen").place(x=80, y=0)  # Menu header

# Item labels with prices
Label(f1, text="Dosa......Rs.60/plate", font=("Lucida Calligraphy", 15, "bold"), fg="black", bg="lightgreen").place(x=10, y=90)
Label(f1, text="Tea.......Rs.10/cup", font=("Lucida Calligraphy", 15, "bold"), fg="black", bg="lightgreen").place(x=10, y=150)
Label(f1, text="Juice.....Rs.30/glass", font=("Lucida Calligraphy", 15, "bold"), fg="black", bg="lightgreen").place(x=10, y=210)
Label(f1, text="Eggs......Rs.15/egg", font=("Lucida Calligraphy", 15, "bold"), fg="black", bg="lightgreen").place(x=10, y=270)

# Frame for the bill section
f3 = Frame(root, bg="lightyellow", highlightbackground="black", highlightthickness=1, height=370, width=300)
f3.place(x=690, y=122)  # Place bill frame at specific coordinates

# Bill section title
Bill = Label(f3, text="Bill", font=("calibri", 30), bg="lightyellow")
Bill.place(x=120, y=20)

# Frame for entry widgets (where the user inputs quantities)
f2 = Frame(root, height=380, width=300, bd=5, relief=RAISED)
f2.pack()  # Place the frame

# Define StringVar variables to hold user input
dosa = StringVar() 
tea = StringVar() 
juice = StringVar() 
eggs = StringVar()
Total_bill = StringVar()  # Holds the total bill amount

# Labels for each item in entry frame
lbl_dosa = Label(f2, font=("aria", 20, "bold"), text="Dosa", width=10, fg="blue4")
lbl_tea = Label(f2, font=("aria", 20, "bold"), text="Tea", width=10, fg="blue4")
lbl_juice = Label(f2, font=("aria", 20, "bold"), text="Juice", width=10, fg="blue4")
lbl_eggs = Label(f2, font=("aria", 20, "bold"), text="Eggs", width=10, fg="blue4")
lbl_dosa.grid(row=1, column=0)
lbl_tea.grid(row=2, column=0)
lbl_juice.grid(row=3, column=0)
lbl_eggs.grid(row=4, column=0)

# Entry fields for each item
entry_dosa = Entry(f2, font=("aria", 20, "bold"), textvariable=dosa, bd=6, width=10, bg="lightpink")
entry_tea = Entry(f2, font=("aria", 20, "bold"), textvariable=tea, bd=6, width=10, bg="lightpink")
entry_juice = Entry(f2, font=("aria", 20, "bold"), textvariable=juice, bd=6, width=10, bg="lightpink")
entry_eggs = Entry(f2, font=("aria", 20, "bold"), textvariable=eggs, bd=6, width=10, bg="lightpink")
entry_dosa.grid(row=1, column=1)
entry_tea.grid(row=2, column=1)
entry_juice.grid(row=3, column=1)
entry_eggs.grid(row=4, column=1)

# Buttons for reset and total calculation
btn_reset = Button(f2, bd=5, fg="black", bg="lightblue", font=("ariel", 16, "bold"), width=12, text="Reset", command=Reset)
btn_reset.grid(row=4, column=0)

btn_total = Button(f2, bd=5, fg="black", bg="lightblue", font=("ariel", 16, "bold"), width=12, text="Total", command=Total)
btn_total.grid(row=4, column=1)

root.mainloop()  # Run the main event loop to keep the window open
