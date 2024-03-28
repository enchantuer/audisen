# Audisen

### To build
```bash
make usb
```
```bash
make simulation
```
```bash
make autotests
```
```bash
make autotests
make simulation
make usb
```

### Usb
Work with .txt, .amp, .ams file
```bash
.\test_usb.exe <file_name>
```

### Simulation
Work with .txt, .ams file, add -play-python if you have the python file named play.py and you have python installed on your computer, (the program run the py command you can change it in python.exe if you want)
```bash
.\test_sim.exe <file_name> [-play-python]
```

### Autotests
You need to have `bohemian_rhapsody.txt` and `bohemian_rhapsody.ams` file in the root folder of the project
```bash
.\test_autotests.exe
```
