import tkinter as tk
from tkinter import filedialog

def open_file():
    file_path = filedialog.askopenfilename(filetypes=[("Text Files", "*.txt")])
    if file_path:
        with open(file_path, "r") as file:
            content = file.read()
            text_widget.delete("1.0", "end")
            text_widget.insert("1.0", content)

def save_file():
    file_path = filedialog.asksaveasfilename(filetypes=[("Text Files", "*.txt")])
    if file_path:
        with open(file_path, "w") as file:
            content = text_widget.get("1.0", "end-1c")
            file.write(content)

root = tk.Tk()
root.title("Text File Editor")

text_widget = tk.Text(root)
text_widget.pack(fill="both", expand=True)

open_button = tk.Button(root, text="Open File", command=open_file)
save_button = tk.Button(root, text="Save File", command=save_file)
open_button.pack()
save_button.pack()

root.mainloop()