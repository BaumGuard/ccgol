# ccgol
Conway's Game of Life in the console

# Description
**ccgol** is a C program that draws [Conway's Game Of Life](https://en.wikipedia.org/wiki/Glider_(Conway%27s_Game_of_Life)) in your terminal window.

## Features
- Generating a random field of alive and dead cells and running the GOL
- Can read a field from a file which can be shifted inside a bigger field
- Automatically recognizes the size of the console window and creates a field of appropriate size in the default mode
- Variable speed
- Automatically stops when it recognizes a final or alternating field configuration

# Installation
Clone **ccgol**:
```
git clone https://github.com/BaumGuard/ccgol
```
Enter the folder of **ccgol**:
```
cd ccgol
```
Compile:
```
make
```
Install:
```
chmod +x install.sh
sudo ./install.sh
```

# Usage
Start **ccgol** from inside its directory:
```
./ccgol
```

## Default mode
If you haven't entered parameters, **ccgol** will run in the default mode, meaning that...
- ...it will operate on a randomly generated field
- ...it will adjust the field size to the console size
- ...it will stop automatically when it recognizes a final or alternating configuration

## Options
### Display options
- `-w`: Set width in characters
- `-h`: Set height in characters
- `-i`: Set speed (milliseconds between two drawings)
- `-r`: Number of runs
- `-inf`: Infinite execution (No check for final or alternating configuration)
- `-init`: Only show initial configuration
- `-help`: Show help dialog

### File options
- `-f`: Path to a field file
- `-x`: Horizontal offset of the imported field in the surrounding field
- `-y`: Vertical offset of the imported field in the surrounding field

### Example
```
./ccgol -w 100 -h 40 -f glider_canon.gol -x 10 -y 5 -i 80
```
#### Explanation
**ccgol** creates an empty field with a **width of 100 characters**, a **height of 40 characters**, imports the field file `glider_canon.gol` and shifts it **10 characters to the right** and **5 characters downwards**. Also the display will **refresh every 80 milliseconds**.

# Field file
**ccgol** enables you to import a field as a file.<br />
In the file the field is represented as a set of lines of 0s and 1s where...
- `0` is a **dead cell**
- `1` is an **alive cell**

**All the lines must be of equal length! Otherways the execution might fail!**

# Uninstall
Enter the directory of **ccgol**:
```
cd ccgol
```
Uninstall:
```
chmod +x uninstall.sh
sudo ./uninstall.sh
```
